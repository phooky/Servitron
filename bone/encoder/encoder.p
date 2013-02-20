.origin 0
.entrypoint START

#define PRU0_ARM_INTERRUPT 19
#define AM33XX

#include "gpio.h"

// All quadrature inputs are on port 1
// Define pins
// 1_16 - Q1A
// 1_17 - Q1B

// number of channels
#define CHANNEL_COUNT 1

// location of channels in memory
#define CHANNEL_START 0x00

.struct Channel
    .u32  position
    .u8   idxA
    .u8   idxB
    .u8   idxIdx
    .u8   state
.ends

.assign Channel, r20, r21, ch

START:
// clear that bit
    LBCO r0, C4, 4, 4
    CLR r0, r0, 4
    SBCO r0, C4, 4, 4

// initialize channels -- this should be done externally
    mov r19, CHANNEL_START
    lbbo ch, r19, 0, SIZE(Channel)
    mov ch.position, 1234
    mov ch.idxA, 16
    mov ch.idxB, 17
    mov ch.idxIdx, 16
    mov ch.state, 0
    sbbo ch, r19, 0, SIZE(Channel)

// set inputs
    mov r17, GPIO1 | GPIO_OE
    lbbo r16, r17, 0, 4  // r16 <- output enable register
    mov r19, CHANNEL_START
    mov r18, CHANNEL_COUNT
init_channel:
    lbbo ch, r19, 0, SIZE(Channel)
    set r16, r16, ch.idxA
    set r16, r16, ch.idxB
    add r19, r19, SIZE(Channel)
    sub r18, r18, 1
    qbne init_channel, r18, 0

// update the output enable register
    sbbo r16, r17, 0, 4
// quadrature table
    mov r14, 0x1b8d72e4
    mov r1, 0x000f0000

sample_port:
    mov r5, GPIO1 | GPIO_DATAIN
    lbbo r4, r5, 0, 4 // r4 <- data channels

    mov r19, CHANNEL_START
    mov r18, CHANNEL_COUNT
process_channel:
    lbbo ch, r19, 0, SIZE(Channel)
    mov r15.b0, 0
    qbbs skip_set_A, r4, ch.idxA
    set r15.b0, r15.b0, 0
skip_set_A:
    qbbs skip_set_B, r4, ch.idxB
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
    sbbo ch, r19, 0, SIZE(Channel)
    add r19, r19, SIZE(Channel)
    sub r18, r18, 1
    qbne process_channel, r18, 0

    mov r4, r15.b0    
    lsl r2, r4, 23 
    MOV r3, GPIO1 | GPIO_SETDATAOUT
    SBBO r2, r3, 0, 4

    mov r7, 100
wait:
    sub r7, r7, 1
    qbne wait, r7, 0

    mov r2, 3
    lsl r2, r2, 23
    mov r3, GPIO1 | GPIO_CLEARDATAOUT
    sbbo r2, r3, 0, 4
    SUB r1, r1, 1
    QBNE sample_port, r1, 0

//#ifdef AM33XX
    // Send notification to Host for program completion
    MOV R31.b0, PRU0_ARM_INTERRUPT+16
//#else
//    MOV R31.b0, PRU0_ARM_INTERRUPT
//#endif

HALT

