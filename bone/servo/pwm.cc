#include "pwm.h"
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
#include <iostream>
#include "util.h"

PWM::PWM(uint16_t frequency) : mem_fd(-1), frequency(frequency)
{
  for (int i = 0; i < 3; i++) {
    pwm_map[i] = 0;
  }
}

const std::string pwm_names[6] = {
  "ehrpwm.0:0",
  "ehrpwm.0:1",
  "ehrpwm.1:0",
  "ehrpwm.1:1",
  "ehrpwm.2:0",
  "ehrpwm.2:1"
};

const std::string prefix = "/sys/class/pwm/";

bool PWM::init() {
  try {
    mem_fd = open("/dev/mem", O_RDWR|O_SYNC);
    if (mem_fd == -1) 
      throw std::runtime_error("Could not open memory map");

    // Switch on all PWM clocks
    uint8_t* cm_map = (uint8_t*)mmap(NULL, CLOCK_MOD_SIZE, PROT_READ|PROT_WRITE,
                        MAP_SHARED, mem_fd, CLOCK_MOD_BASE);
    if (cm_map == MAP_FAILED) 
      throw new std::runtime_error("Could not map clock module");
    *((uint32_t*)(cm_map + CLOCK_MOD_PER_EPWMSS0_CLKCTRL)) = 0x02;
    *((uint32_t*)(cm_map + CLOCK_MOD_PER_EPWMSS1_CLKCTRL)) = 0x02;
    *((uint32_t*)(cm_map + CLOCK_MOD_PER_EPWMSS2_CLKCTRL)) = 0x02;
    munmap(cm_map, CLOCK_MOD_SIZE);

    // mux all the pins
    writePath("/sys/kernel/debug/omap_mux/mcasp0_fsx", 1); // 0:0
    writePath("/sys/kernel/debug/omap_mux/mcasp0_aclkx", 1); // 0:1
    writePath("/sys/kernel/debug/omap_mux/gpmc_a2", 6); // 1:0
    writePath("/sys/kernel/debug/omap_mux/gpmc_a3", 6); // 1:1
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad8", 4); // 2:0
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad9", 4); // 2:1
    // Set up all clocks through the filesystem
    for (int i = 0; i < 6; i++) {
      writePath(prefix+pwm_names[i]+"/run",0);
      writePath(prefix+pwm_names[i]+"/duty_percent",0, false);
      writePath(prefix+pwm_names[i]+"/period_freq",1000, false);
      writePath(prefix+pwm_names[i]+"/run",1);
    }

    // Map all pwm register banks
    pwm_map[0] = (uint8_t*)mmap(NULL, PWMSS_SIZE, PROT_READ|PROT_WRITE,
                                MAP_SHARED, mem_fd, PWMSS0_BASE);
    pwm_map[1] = (uint8_t*)mmap(NULL, PWMSS_SIZE, PROT_READ|PROT_WRITE,
                                MAP_SHARED, mem_fd, PWMSS1_BASE);
    pwm_map[2] = (uint8_t*)mmap(NULL, PWMSS_SIZE, PROT_READ|PROT_WRITE,
                                MAP_SHARED, mem_fd, PWMSS2_BASE);
  } catch (std::runtime_error& ex) {
    std::cout << ex.what();
    shutdown();
    return false;
  }
  return true;
}

void PWM::setChannel(int channel, int value) {
  if (channel >= PWM_MAX || channel < 0) return;
  switch (channel) {
  case PWM0A:
    *((uint16_t*)(pwm_map[0]+EPWM_CMPA)) = value;
    break;
  case PWM0B:
    *((uint16_t*)(pwm_map[0]+EPWM_CMPB)) = value;
    break;
  case PWM1A:
    *((uint16_t*)(pwm_map[1]+EPWM_CMPA)) = value;
    break;
  case PWM1B:
    *((uint16_t*)(pwm_map[1]+EPWM_CMPB)) = value;
    break;
  case PWM2A:
    *((uint16_t*)(pwm_map[2]+EPWM_CMPA)) = value;
    break;
  case PWM2B:
    *((uint16_t*)(pwm_map[2]+EPWM_CMPB)) = value;
    break;
  }
}

void PWM::shutdown() {
  for (int i = 0; i < 6; i++) {
    writePath(prefix+pwm_names[i]+"/run",0);
  }
  // don't bother to unmux pins for now
  for (int i = 0; i < 3; i++) {
    if (pwm_map[i] != 0) {
      munmap(pwm_map[i], PWMSS_SIZE);
    }
  }
  if (mem_fd != -1) {
    close(mem_fd);
  }
}
