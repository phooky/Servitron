// GPIO bank locations
#ifdef AM33XX
#define EPWM0_BASE 0x48300000 
#define EPWM1_BASE 0x48302000 
#define EPWM2_BASE 0x48304000UL
#define CLOCK_MOD_BASE 0x44e00000

#else
#error PWM registers not defined for chip.
#endif

// Clock module offsets
#define CM_PER_EPWMSS1_CLKCTRL 0xcc
#define CM_PER_EPWMSS0_CLKCTRL 0xd4
#define CM_PER_EPWMSS2_CLKCTRL 0xd8

// Time base offsets
#define EPWM_TBCNT 0x208
#define EPWM_TBPRD 0x20a
// ePWM offsets
#define EPWM_CMPA 0x212
#define EPWM_CMPB 0x214
#define EPWM_SIZE 0x226
