#ifndef CONFIG_H
#define CONFIG_H

// All inputs are on port 1
#define Q0A 6
#define Q0B 7
#define Q0I 2

#define Q1A 3
#define Q1B 13
#define Q1I 12

#define Q2A 15
#define Q2B 14
#define Q2I 31

#define Q3A 30
#define Q3B 5
#define Q3I 4

#define Q4A 1
#define Q4B 0
#define Q4I 29

#define Q5A 28
#define Q5B 16
#define Q5I 17

// All motor outputs are on port 2
#define M0A 6
#define M0B 7

//
// Memory map:
// 0x00 Quadstate[6]
// 0x100 Report
#define QUAD_COUNT 6
#define QUAD_STATE_BASE 0x00
#define REPORT_BASE 0x100

#endif // CONFIG_H
