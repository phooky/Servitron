// GPIO bank locations
#ifdef AM33XX
#define EPWM0_BASE 0x48300200 
#define EPWM1_BASE 0x48302200 
#define EPWM2_BASE 0x48304200
#define CLOCK_MOD_BASE 0x44e00000

#else
#error PWM registers not defined for chip.
#endif

// Clock module offsets
#define CM_PER_EPWMSS1_CLKCTRL 0xcc
#define CM_PER_EPWMSS0_CLKCTRL 0xd4
#define CM_PER_EPWMSS2_CLKCTRL 0xd8

// PWMSS module offsets
#define PWMSS_IDVER     0x0
#define PWMSS_SYSCONFIG 0x4
#define PWMSS_CLKCONFIG 0x8
#define PWMSS_CLKSTATUS 0xc

// ePWM offsets
#define EPWM_CMPA 0x12
#define EPWM_CMPB 0x14
#define EPWM_SIZE 0x26
