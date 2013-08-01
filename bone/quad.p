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
    mov r19, QUAD_STATE_BASE            // r19 <- address of current axis 
    mov r18, QUAD_COUNT                 // r18 <- loop counter

init_channel:
    // Initialize the direction of each pin
    lbbo ch, r19, 0, SIZE(QuadState)    // load current axis state
    set r16, r16, ch.pinA               // \
    set r16, r16, ch.pinB               // -- set direction bit for each pin
    set r16, r16, ch.pinIdx             // /
    add r19, r19, SIZE(QuadState)       // increment current axis addresss
    sub r18, r18, 1                     // decrement loop counter
    qbne init_channel, r18, 0           // next axis
   
    sbbo r16, r17, 0, 4                 // store r16 to the gpio2 output enable reg
    mov r14, 0x1b8d72e4                 // r14 <- quadrature state table

// r6 will hold the value of the cycle time throughout.
// To change the cycle time, you'll need to restart
// the PRU.
   mov r7, CYCLE_COUNT_BASE
   lbbo r6, r7, 0, 4

// Set the control status bit.
// r7 will hold the control register base throughout.
    mov r7, PRU0_CONTROL_REGISTERS
    lbbo r8, r7, PRU_CR_CONTROL, 4
    set r8, r8, 3
    sbbo r8, r7, PRU_CR_CONTROL, 4

// r5 will hold the gpio port address throughout
    mov r5, GPIO2_BASE | GPIO_DATAIN
// ----
// This is the main quad loop.
//
    mov r29, 0
outer_loop:

    add r29, r29, 1
    //mov r19, QUAD_STATE_BASE
    //sbbo r29, r18, 0, 4 // < save counter
sample_port:
    lbbo r4, r5, 0, 4 // r4 <- data channels

    mov r19, QUAD_STATE_BASE
    mov r18, QUAD_COUNT

process_channel:
    lbbo ch, r19, 0, SIZE(QuadState)
    mov r15.b0, 0 // new state
    
    qbbs skip_set_A, r4, ch.pinA
    set r15.b0, r15.b0, 0
skip_set_A:
    qbbs skip_set_B, r4, ch.pinB
    set r15.b0, r15.b0, 1
skip_set_B:

    // compute offset
    lsl r15.b2, ch.state, 2
    or r15.b2, r15.b2, r15.b0
    lsl r15.b2, r15.b2, 1
    lsr r13, r14, r15.b2
    and r13, r13, 0x3
    // switch based on table
    qbne sw_2, r13, 1
sw_1:
    add ch.position, ch.position, 1
sw_2:
    qbne sw_3, r13, 2
    sub ch.position, ch.position, 1
sw_3:
    qbne sw_end, r13, 3
    // error condition
sw_end:

    mov ch.state, r15.b0
    // save state
    sbbo ch, r19, 0, SIZE(QuadState)
    add r19, r19, SIZE(QuadState)
    sub r18, r18, 1
    qbne process_channel, r18, 0

    // Check for timeout
    lbbo r8, r7, PRU_CR_CYCLE, 4
    qblt sample_port, r6, r8

    // Stop cycle counting
    lbbo r9, r7, PRU_CR_CONTROL, 4
    clr r9, r9, 3
    sbbo r9, r7, PRU_CR_CONTROL, 4

    // Copy report? Todo.

    // Set cycle counter
    sub r8, r8, r6
    sbbo r8, r7, PRU_CR_CYCLE, 4

    // Restart cycle counter
    set r9, r9, 3
    sbbo r9, r7, PRU_CR_CONTROL, 4

    // Send interrupt
    MOV R31.b0, PRU0_ARM_INTERRUPT+16

    jmp outer_loop
HALT

