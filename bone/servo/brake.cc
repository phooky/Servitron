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

// Brake is on port 0, pin 26
std::string outputPinName = "gpmc_ad10";


Brake::Brake() {}

bool Brake::init() {
  writePath(std::string("/sys/kernel/debug/omap_mux/")+*outputPinName, 0x0f);
  gpioFd = open("/dev/mem", O_RDWR|O_SYNC);
  if (gpioFd == -1) 
    throw std::runtime_error("Could not open memory map");
  gpioMap = (uint8_t*)mmap(NULL, GPIO_SIZE, PROT_READ|PROT_WRITE,
                        MAP_SHARED, gpioFd, GPIO0_BASE);
  if (gpioMap == MAP_FAILED) 
      throw new std::runtime_error("Could not map gpio module");
  // set as outputs
  for (int i = 0; i < 6; i++) {
    allpins |= 1 << pinA[i];
    allpins |= 1 << pinB[i];
  }
  // brake on!
  *((uint32_t*)(gpioMap+GPIO_DATAOUT)) &= ~(1 << BRAKE_PIN);
  // set as output
  *((uint32_t*)(gpioMap+GPIO_OE)) &= ~(1 << BRAKE_PIN)
  // brake on!
  *((uint32_t*)(gpioMap+GPIO_DATAOUT)) &= ~(1 << BRAKE_PIN);
}

void Brake::shutdown() {
  // brake on!
  *((uint32_t*)(gpioMap+GPIO_DATAOUT)) &= ~(1 << BRAKE_PIN);
  munmap(gpioMap, GPIO_SIZE);
  close(gpioFd);
}

void Brake::setBrake(bool on) {
  if (on) {
    *((uint32_t*)(gpioMap+GPIO_DATAOUT)) &= ~(1 << BRAKE_PIN);
  } else {
    *((uint32_t*)(gpioMap+GPIO_DATAOUT)) |= 1 << BRAKE_PIN;
  }
}

