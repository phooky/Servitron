#ifndef QUAD_SHARED_H
#define QUAD_SHARED_H

// Memory map:
// 0x00 Quadstate[6]
// 0x100 Report
#define QUAD_COUNT 6

#define QUAD_STATE_BASE 0x00
//
// Quadrature channel state:
//     0       1       2       3
// ---------------------------------
// |       channel position        |
// ---------------------------------
// | state | pin A | pin B | pin I |
// ---------------------------------
// |  error count  |
// -----------------
//
//

// Report status is a simple synchronization
// mechanism for report data. The report status
// is one byte. When the cortex-a8 is ready for
// a new report, the report status is set by that
// processor to 0xFF. When a report has been
// written, the report status is set to the
// number of interrupt cycles that have occurred
// since the last report was written (ordinarily
// 1 if the processor is handling the quadrature
// data quickly enough). If the number of reports
// is too large, consider changing the cycle
// count.
// set to 0xFF
//
#define REPORT_STATUS_ADDR 0xfa

#define CYCLE_COUNT_ADDR 0xfc
#define REPORT_BASE 0x100
//
// Report:
//     0       1       2       3
// ---------------------------------
// |       channel position        |
// ---------------------------------
// |  error count  |
// -----------------
//


#endif // QUAD_SHARED_H
