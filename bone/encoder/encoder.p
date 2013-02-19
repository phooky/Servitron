.origin 0
.entrypoint START

#define PRU0_ARM_INTERRUPT 19
#define AM33XX

#include "gpio.h"

START:
// clear that bit
    LBCO r0, C4, 4, 4
    CLR r0, r0, 4
    SBCO r0, C4, 4, 4

// set 16 and 17 as inputs
    mov r3, GPIO1 | GPIO_OE
    lbbo r1, r3, 0, 4
    ldi r2, 3
    lsl r2, r2, 16
    or r1, r1, r2
    sbbo r1, r3, 0, 4

    MOV r1, 0x00f00000
BLINK:
    mov r5, GPIO1 | GPIO_DATAIN
    lbbo r4, r5, 0, 4
    lsr r4, r4, 16
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
    QBNE BLINK, r1, 0

//#ifdef AM33XX
    // Send notification to Host for program completion
    MOV R31.b0, PRU0_ARM_INTERRUPT+16
//#else
//    MOV R31.b0, PRU0_ARM_INTERRUPT
//#endif

HALT

