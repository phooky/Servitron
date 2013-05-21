#include "../motor.h"
#include <stdint.h>
#include "../am335x_regs.h"
#include "pinconfig.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>

static uint8_t* gpioMap;
static int gpioFd;

static int pwmFd;
static uint8_t* pwmMap[3];

static uint32_t allpins = 0;

bool motor::init() {
    gpioFd = open("/dev/mem", O_RDWR|O_SYNC);
    if (gpioFd == -1) {
        throw std::runtime_error("Could not open memory map");
    }
    gpioMap = (uint8_t*)mmap(NULL, GPIO_SIZE, PROT_READ|PROT_WRITE,
                                      MAP_SHARED, gpioFd, GPIO2_BASE);
    if (gpioMap == MAP_FAILED) {
        throw new std::runtime_error("Could not map gpio module");
    }
    // set as outputs
    for (int i = 0; i < 6; i++) {
         allpins |= 1 << servoConfig[i].motorA;
         allpins |= 1 << servoConfig[i].motorB;
    }
    *((uint32_t*)(gpioMap+GPIO_OE)) &= ~allpins;
    // set in gnd brake mode
    *((uint32_t*)(gpioMap+GPIO_DATAOUT)) &= ~allpins;
    return true;
}

void motor::shutdown() {
    for (int i = 0; i < 6; i++) {
        motor::setPower(i,0);
    }
    *((uint32_t*)(gpioMap+GPIO_DATAOUT)) &= ~allpins;
    munmap(gpioMap, GPIO_SIZE);
    close(gpioFd);
}

void motor::setPower(int channel, int value) {
}

