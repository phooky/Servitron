#ifndef QUAD_SHARED_H
#define QUAD_SHARED_H

// Memory map:
// 0x00 Quadstate[6]
// 0x100 Report
#define QUAD_COUNT 6

#define QUAD_STATE_BASE 0x00
/**
 * Quadrature channel state:
 *     0       1       2       3
 * ---------------------------------
 * |       channel position        |
 * ---------------------------------
 * | state | pin A | pin B | pin I |
 * ---------------------------------
 * |  error count  |
 * -----------------
 *
 */

#define CYCLE_COUNT_BASE 0xfc
#define REPORT_BASE 0x100

#endif // QUAD_SHARED_H
