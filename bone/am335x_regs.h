#ifndef AM335X_REGS
#define AM335X_REGS

// Register locations for the AM335x chips

// --

// Clock module base and size
#define CLOCK_MOD_BASE 0x44e00000
#define CLOCK_MOD_SIZE 0x400

// Clock module offsets
#define CLOCK_MOD_PER_EPWMSS0_CLKCTRL 0xd4
#define CLOCK_MOD_PER_EPWMSS1_CLKCTRL 0xcc
#define CLOCK_MOD_PER_EPWMSS2_CLKCTRL 0xd8

// --

// PWM subsystem base addresses
#define PWMSS0_BASE 0x48300000 
#define PWMSS1_BASE 0x48302000 
#define PWMSS2_BASE 0x48304000
#define PWMSS_SIZE 0x1000

// Time base offsets (relative to pwmss base)
#define EPWM_TBCNT 0x208
#define EPWM_TBPRD 0x20a
// ePWM offsets (relative to pwmss base)
#define EPWM_CMPA 0x212
#define EPWM_CMPB 0x214
#define EPWM_SIZE 0x226

// --

// GPIO bank locations
#define GPIO0_BASE 0x44e07000
#define GPIO1_BASE 0x4804c000
#define GPIO2_BASE 0x481ac000
#define GPIO3_BASE 0x481ae000
#define GPIO_SIZE 0x1000

// GPIO register offsets 
#define GPIO_REVISION	     0x0
#define GPIO_SYSCONFIG       0x10
#define GPIO_IRQSTATUS_RAW_0 0x24
#define GPIO_IRQSTATUS_RAW_1 0X28
#define GPIO_IRQSTATUS_0     0x2c
#define GPIO_IRQSTATUS_1     0x30
#define GPIO_IRQSTATUS_SET_0 0x34
#define GPIO_IRQSTATUS_SET_1 0x38
#define GPIO_IRQSTATUS_CLR_0 0x3c
#define GPIO_IRQSTATUS_CLR_1 0x40
#define GPIO_IRQWAKEN_0      0x44
#define GPIO_IRQWAKEN_1      0x48
#define GPIO_SYSSTATUS       0x114
#define GPIO_CTRL            0x130
#define GPIO_OE              0x134
#define GPIO_DATAIN          0x138
#define GPIO_DATAOUT         0x13c
#define GPIO_LEVELDETECT0    0x140
#define GPIO_LEVELDETECT1    0x144
#define GPIO_RISINGDETECT    0x148
#define GPIO_FALLINGDETECT   0x14c
#define GPIO_DEBOUNCEENABLE  0x150
#define GPIO_DEBOUNCINGTIME  0x154
#define GPIO_CLEARDATAOUT    0x190
#define GPIO_SETDATAOUT	     0x194

#endif // AM335X_REGS
