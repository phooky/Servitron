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
#include "config.h"

int pwmChannel[6] = { M0P, M1P, M2P, M3P, M4P, M5P };
int pinA[6] = { M0A, M1A, M2A, M3A, M4A, M5A };
int pinB[6] = { M0B, M1B, M2B, M3B, M4B, M5B };

std::string outputPinNames[] = {
  "lcd_data0",
  "lcd_data1",
  "lcd_data2",
  "lcd_data3",
  "lcd_data4",
  "lcd_data5",
  "lcd_data6",
  "lcd_data7",
  "lcd_vsync",
  "lcd_pclk",
  "lcd_hsync",
  "lcd_ac_bias_en",
  ""
};

uint32_t allpins = 0;

Motor::Motor(PWM& pwm) :
  pwm(pwm) {
}

bool Motor::init() {
  std::string *names = outputPinNames;
  while (! names->empty()) {
    writePath(std::string("/sys/kernel/debug/omap_mux/")+*names, 0x0f);
    names++;
  }
  gpioFd = open("/dev/mem", O_RDWR|O_SYNC);
  if (gpioFd == -1) 
    throw std::runtime_error("Could not open memory map");
  gpioMap = (uint8_t*)mmap(NULL, GPIO_SIZE, PROT_READ|PROT_WRITE,
                        MAP_SHARED, gpioFd, GPIO2_BASE);
  if (gpioMap == MAP_FAILED) 
      throw new std::runtime_error("Could not map gpio module");
  // set as outputs
  for (int i = 0; i < 6; i++) {
    allpins |= 1 << pinA[i];
    allpins |= 1 << pinB[i];
  }
  *((uint32_t*)(gpioMap+GPIO_OE)) &= ~allpins;
  // set in gnd brake mode
  *((uint32_t*)(gpioMap+GPIO_DATAOUT)) &= ~allpins;
}

void Motor::shutdown() {
  // for safety set data pins low and turn off pwm
  for (int i = 0; i < 6; i++) {
    pwm.setChannel(pwmChannel[i], 0);
  }
  *((uint32_t*)(gpioMap+GPIO_DATAOUT)) &= ~allpins;
  munmap(gpioMap, GPIO_SIZE);
  close(gpioFd);
}

// Set the motor to the specified
// power. 0 is off. Negative values are CCW, positive
// are CW.
void Motor::setPower(int channel, int value) {
  const int bitA = 1 << pinA[channel];
  const int bitB = 1 << pinB[channel];
  uint32_t portVal = *((uint32_t*)(gpioMap+GPIO_DATAOUT));
  if (value == 0) {
    portVal &= ~bitA;
    portVal &= ~bitB;
    pwm.setChannel(pwmChannel[channel], 0);
    *((uint32_t*)(gpioMap+GPIO_DATAOUT)) = portVal & ~(bitA | bitB);
  } else if (value > 0) {
    portVal |= bitA;
    portVal &= ~bitB;
  } else if (value < 0) {
    portVal &= ~bitA;
    portVal |= bitB;
    value = -value;
  }
  pwm.setChannel(pwmChannel[channel], value);
  *((uint32_t*)(gpioMap+GPIO_DATAOUT)) = portVal;
}
    

