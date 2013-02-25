.origin 0
.entrypoint START

#define PRU0_ARM_INTERRUPT 0x03
#define PRU0_INTERRUPT_STROBE 0x10
#include "am335x_regs.h"
#include "config.h"

// All quadrature inputs are on port 1

.struct QuadState
    .u32  position
    .u8   state
    .u8   pinA 
    .u8   pinB
    .u8   pinIdx
    .u16  errCount
.ends

.assign QuadState, r20, r22.w0, ch

START:
// On the PRUv2 (PRU-ICSS version), C4 is the constant
// table entry for the PRU-ICSS config register block;
// 0x4 is the address of the SYSCFG register. Clearing
// bit 4 of this register turns off standby mode.
    LBCO r0, C4, 4, 4
    CLR r0, r0, 4
    SBCO r0, C4, 4, 4

// set inputs
    mov r17, GPIO1_BASE | GPIO_OE
    lbbo r16, r17, 0, 4  // r16 <- output enable register
    mov r19, QUAD_STATE_BASE
    mov r18, QUAD_COUNT
init_channel:
    lbbo ch, r19, 0, SIZE(QuadState)
    set r16, r16, ch.pinA
    set r16, r16, ch.pinB
    set r16, r16, ch.pinIdx
    add r19, r19, SIZE(QuadState)
    sub r18, r18, 1
    qbne init_channel, r18, 0

// update the output enable register
    sbbo r16, r17, 0, 4
// load quadrature table
    mov r14, 0x1b8d72e4
    mov r1, 0x000f0000

// r5 will hold the gpio port address throughout
    mov r5, GPIO1_BASE | GPIO_DATAIN
// ----
// This is the main quad loop.
//
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

    sbbo r2, r3, 0, 4
    SUB r1, r1, 1
    QBNE sample_port, r1, 0

    MOV R31.b0, PRU0_ARM_INTERRUPT|PRU0_INTERRUPT_STROBE

HALT

