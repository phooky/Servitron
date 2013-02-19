// GPIO bank locations
#ifdef AM33XX
#define GPIO0 0x44e07000
#define GPIO1 0x4804c000
#define GPIO2 0x481ac000
#define GPIO3 0x481ae000
#else
#error GPIO ports not defined for chip.
#endif

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
