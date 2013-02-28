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
#define M0P 0

#define M1A 8
#define M1B 9
#define M1P 1

#define M2A 10
#define M2B 11
#define M2P 2

#define M3A 12
#define M3B 13
#define M3P 3

#define M4A 23
#define M4B 25
#define M4P 4

#define M5A 22
#define M5B 24
#define M5P 5


//
// Memory map:
// 0x00 Quadstate[6]
// 0x100 Report
#define QUAD_COUNT 6

#define QUAD_STATE_BASE 0x00
#define CYCLE_COUNT_BASE 0xfc
#define REPORT_BASE 0x100

#endif // CONFIG_H
