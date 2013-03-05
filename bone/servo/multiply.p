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

.macro mult16to32
.mparam out, a, b
    mov out, 0
    signextend16 a
    signextend16 b
    // r26.b0 is the counter
    // r27 is the shift result
    mov r26.b0, 0
multloop:
    qbbc skipadd, b, r26.b0
    lsl r27, a, r26.b0
    add out, out, r27
skipadd:
    add r26.b0, r26.b0, 1
    qbgt multloop, r26.b0, 32
.endm

.macro mult32to64
.mparam outLo, outHi, a, b
    mov outLo, 0
    mov outHi, 0
    // r26.b0 is the counter
    // r26.b1 is 32-r6.b0
    // r27-r28 is the shift result
    mov r26.b0, 0
    mov r26.b1, 31
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
.endm
