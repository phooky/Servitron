.origin 0
.entrypoint START

// memory locations
#include "../../multiply.p"

#include "pru_mem.h"

#define PRU0_ARM_INTERRUPT 19


START:
    // r2 - A
    // r3 - B
    // r4, r5, r6 - OUT
    lbco r2, c24, A, 4
    lbco r3, c24, B, 4
    mult16to32 r4, r2, r3
    //signextend16 r2
    sbco r4, c24, OUT32, 4
    lbco r2, c24, A, 4
    lbco r3, c24, B, 4
    mult32to64 r4, r5, r2, r3
    sbco r4, c24, OUT64LO, 4
    sbco r5, c24, OUT64HI, 4
    lbco r2, c24, A, 4
    lbco r3, c24, B, 4
    mult32to32 r4, r2, r3
    sbco r4, c24, OUT32B
    // Send interrupt
    MOV R31.b0, PRU0_ARM_INTERRUPT+16
HALT
