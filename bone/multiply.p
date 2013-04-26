//
// r26-r29 are considered scratch registers.
// 


.macro signextend16
.mparam reg
    mov reg.w2, 0
    qbbc no_sign, reg, 15
    mov reg.w2, 0xffff
no_sign:
.endm

.macro marksign32
.mparam value, mark, scrap
    qbbc no_mark, value, 31
    mov scrap, 0
    sub value, scrap, value
    xor mark, mark, 1
no_mark:
.endm

.macro mult16to32
.mparam out, a, b
    mov out, 0
    // r26.b0 is the counter
    // r26.b1 is the result sign
    // r27 is the shift result
    mov r26.b0, 0
    mov r26.b1, 0
    marksign32 a, r26.b1, r27
    marksign32 b, r26.b1, r27
multloop:
    qbbc skipadd, b, r26.b0
    lsl r27, a, r26.b0
    add out, out, r27
skipadd:
    add r26.b0, r26.b0, 1
    qbgt multloop, r26.b0, 16
    qbbc skipinv, r26.b1, 0
    mov r27, 0
    sub out, r27, out
skipinv:
.endm

.macro mult32to64
.mparam outLo, outHi, a, b
    mov outLo, 0
    mov outHi, 0
    // r26.b0 is the counter
    // r26.b1 is 32-r6.b0
    // r26.b2 is the result sign
    // r27-r28 is the shift result
    mov r26.b0, 0
    mov r26.b1, 31
    mov r26.b2, 0
    marksign32 a, r26.b2, r27
    marksign32 b, r26.b2, r27
multloop:
    qbbc skipadd, b, r26.b0
    lsl r27, a, r26.b0
    lsr r28, a, r26.b1
    add outLo, outLo, r27
    adc outHi, outHi, r28
skipadd:
    add r26.b0, r26.b0, 1
    sub r26.b1, r26.b1, 1
    qbgt multloop, r26.b0, 32
    qbbc skipinv, r26.b2, 0
    mov r27, 0
    sub outLo, r27, outLo
    suc outHi, r27, outHi
skipinv:
.endm

        // TODO -- IMPLEMENT
.macro mult32to32
.mparam out, a, b
    mov outLo, 0
    mov outHi, 0
    // r26.b0 is the counter
    // r26.b1 is 32-r6.b0
    // r26.b2 is the result sign
    // r27-r28 is the shift result
    mov r26.b0, 0
    mov r26.b1, 31
    mov r26.b2, 0
    marksign32 a, r26.b2, r27
    marksign32 b, r26.b2, r27
multloop:
    qbbc skipadd, b, r26.b0
    lsl r27, a, r26.b0
    lsr r28, a, r26.b1
    add outLo, outLo, r27
    adc outHi, outHi, r28
skipadd:
    add r26.b0, r26.b0, 1
    sub r26.b1, r26.b1, 1
    qbgt multloop, r26.b0, 32
    qbbc skipinv, r26.b2, 0
    mov r27, 0
    sub outLo, r27, outLo
    suc outHi, r27, outHi
skipinv:
.endm
