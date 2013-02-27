#include "motor.h"
#include "util.h"
#include "am335x_regs.h"
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <stdexcept>

Motor::Motor(PWM& pwm, int pwmChannel, int pinA, int pinB,
             const std::string muxA, const std::string muxB) :
  pwm(pwm), pwmChannel(pwmChannel), pinA(pinA), pinB(pinB),
  muxA(muxA), muxB(muxB) {
}

bool Motor::init() {
  writePath(std::string("/sys/kernel/debug/omap_mux/")+muxA, 0x07);
  writePath(std::string("/sys/kernel/debug/omap_mux/")+muxB, 0x07);
  gpioFd = open("/dev/mem", O_RDWR|O_SYNC);
  if (gpioFd == -1) 
    throw std::runtime_error("Could not open memory map");
  gpioMap = (uint8_t*)mmap(NULL, GPIO_SIZE, PROT_READ|PROT_WRITE,
                        MAP_SHARED, gpioFd, GPIO2_BASE);
  if (gpioMap == MAP_FAILED) 
      throw new std::runtime_error("Could not map gpio module");
  // set as outputs
  *((uint32_t*)(gpioMap+GPIO_OE)) &= ~((1<<pinA) | (1<<pinB));
  // set in gnd brake mode
  *((uint32_t*)(gpioMap+GPIO_DATAOUT)) &= ~((1<<pinA) | (1<<pinB));
}


void Motor::shutdown() {
  // for safety set data pins low and turn off pwm
  pwm.setChannel(pwmChannel, 0);
  *((uint32_t*)gpioMap+GPIO_DATAOUT) &= ~((1<<pinA) | (1<<pinB));
  munmap(gpioMap, GPIO_SIZE);
  close(gpioFd);
}

// Set the motor to the specified
// power. 0 is off. Negative values are CCW, positive
// are CW.
void Motor::setPower(int value) {
  uint32_t portVal = *((uint32_t*)gpioMap+GPIO_DATAOUT);
  if (value == 0) {
    portVal &= ~(1<<pinA);
    portVal &= ~(1<<pinB);
    pwm.setChannel(pwmChannel, 0);
    *((uint32_t*)gpioMap+GPIO_DATAOUT) = portVal & ~((1<<pinA) | (1<<pinB));
  } else if (value > 0) {
    portVal |= 1<<pinA;
    portVal &= ~(1<<pinB);
  } else if (value < 0) {
    portVal &= ~(1<<pinA);
    portVal |= 1<<pinB;
    value = -value;
  }
  pwm.setChannel(pwmChannel, value);
  *((uint32_t*)gpioMap+GPIO_DATAOUT) = portVal;
}
    

