#ifndef QUAD_SHARED_H
#define QUAD_SHARED_H

// Memory map:
// 0x00 Quadstate[6]
// 0x100 Report
#define QUAD_COUNT 6

#define QUAD_STATE_BASE 0x00
#define CYCLE_COUNT_BASE 0xfc
#define REPORT_BASE 0x100

#endif // QUAD_SHARED_H
