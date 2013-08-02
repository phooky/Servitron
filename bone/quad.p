.origin 0
.entrypoint START

#define PRU0_ARM_INTERRUPT 19
#define PRU0_CONTROL_REGISTERS 0x00022000
#define PRU_CR_CONTROL 0x00
#define PRU_CR_CYCLE   0x0c

#include "am335x_regs.h"
#include "quad_shared.h"

// All quadrature inputs are on port 1

.struct QuadState
    .u32  position
    .u8   state
    .u8   pinA 
    .u8   pinB
    .u8   pinIdx
    .u16  errCount
.ends

.assign QuadState, r20, r22.w0, ch  // r20 - r22.w0 <- current axis state

START:
// On the PRUv2 (PRU-ICSS version), C4 is the constant
// table entry for the PRU-ICSS config register block;
// 0x4 is the address of the SYSCFG register. Clearing
// bit 4 of this register turns off standby mode.
    LBCO r0, C4, 4, 4
    CLR r0, r0, 4
    SBCO r0, C4, 4, 4

    // The next section may be obsolete if the quadrature
    // pins are correctly muxed by the device tree.

    // Set all GPIO2 pins as inputs.
    mov r17, GPIO2_BASE | GPIO_OE       // r17 <- address of gpio2 output enable reg
    lbbo r16, r17, 0, 4                 // r16 <- output enable register
    mov r19, QUAD_STATE_BASE            // r19 <- address of current channel 
    mov r18, QUAD_COUNT                 // r18 <- loop counter

init_channel:
    // Initialize the direction of each pin
    lbbo ch, r19, 0, SIZE(QuadState)    // load current channel state
    set r16, r16, ch.pinA               // \
    set r16, r16, ch.pinB               // -- set direction bit for each pin
    set r16, r16, ch.pinIdx             // /
    add r19, r19, SIZE(QuadState)       // increment current channel addresss
    sub r18, r18, 1                     // decrement loop counter
    qbne init_channel, r18, 0           // next channel
   
    sbbo r16, r17, 0, 4                 // store r16 to the gpio2 output enable reg
    mov r14, 0x1b8d72e4                 // r14 <- quadrature state table

    mov r7, CYCLE_COUNT_ADDR            // r7 <- address in sram of cycles/report
    lbbo r6, r7, 0, 4                   // r6 <- cycles/report as spec. by user

                                        // Turn on the PRU cycle counters
    mov r7, PRU0_CONTROL_REGISTERS      // r7 <- address of PRU0 control register
    lbbo r8, r7, PRU_CR_CONTROL, 4      // r8 <- PRU0 control register
    set r8, r8, 3                       // set bit 3 (COUNTENABLE)
    sbbo r8, r7, PRU_CR_CONTROL, 4      // PRU0 control register <- r8

    mov r5, GPIO2_BASE | GPIO_DATAIN    // r5 <- gpio2 input register

outer_loop:                             // MAIN QUADRATURE LOOP

    lbbo r4, r5, 0, 4                   // r4 <- gpio2 pin values
    mov r19, QUAD_STATE_BASE            // r19 <- address of current channel
    mov r18, QUAD_COUNT                 // r18 <- channel loop counter

process_channel:
    lbbo ch, r19, 0, SIZE(QuadState)    // Load current channel state
    mov r15.b0, 0                       // r15.b0 <- 0
    
    qbbs skip_set_A, r4, ch.pinA        // if pinA is not set
    set r15.b0, r15.b0, 0               // r15.b0 |= 0x01
skip_set_A:
    qbbs skip_set_B, r4, ch.pinB        // if pinB is not set
    set r15.b0, r15.b0, 1               // r15.b0 |= 0x02
skip_set_B:

                                        // compute lookup table index in r15.b2
    lsl r15.b2, ch.state, 2             // r15.b2 = (ch.state << 2) | r15.b0
    or r15.b2, r15.b2, r15.b0
    lsl r15.b2, r15.b2, 1               // r15.b2 <<= 1 
    lsr r13, r14, r15.b2                // r13 = (table >> r15.b2) & 0x03
    and r13, r13, 0x3
    qbne sw_2, r13, 1                   // switch on r13
sw_1:
    add ch.position, ch.position, 1     // if r13 == 1 then position += 1
sw_2:
    qbne sw_3, r13, 2
    sub ch.position, ch.position, 1     // if r13 == 2 then position -= 1
sw_3:
    qbne sw_end, r13, 3                 // if r13 == 3 then position unchanged

    add ch.errCount, ch.errCount, 1     // otherwise, an error has occurred
sw_end:

    mov ch.state, r15.b0                // new state <- r15.b0
    sbbo ch, r19, 0, SIZE(QuadState)    // Save current channel state
    add r19, r19, SIZE(QuadState)       // increment current channel addresss
    sub r18, r18, 1                     // decrement loop counter
    qbne process_channel, r18, 0        // next channel

                                        // All channels have been processed.
    lbbo r8, r7, PRU_CR_CYCLE, 4        // r8 <- PRU cycle count
    qblt outer_loop, r6, r8             // if not over limit, back to loop

    lbbo r9, r7, PRU_CR_CONTROL, 4      // r9 <- PRU control register
    clr r9, r9, 3                       // disable COUNTENABLE pin
    sbbo r9, r7, PRU_CR_CONTROL, 4      // PRU control register <- r9

    sub r8, r8, r6                      // r8 <- cycle count - limit
    sbbo r8, r7, PRU_CR_CYCLE, 4        // PRU cycle count <- r8
    set r9, r9, 3                       // enable COUNTENABLE pin
    sbbo r9, r7, PRU_CR_CONTROL, 4      // PRU control register <- r9


    // TODO: copy report, check retrieve bit?

    MOV R31.b0, PRU0_ARM_INTERRUPT+16   // Send interrupt to cortex-a8
    jmp outer_loop                      // back to loop
HALT

