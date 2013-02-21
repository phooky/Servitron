#ifndef PWM_H
#define PWM_H

#include <stdint.h>

class PWM {
private:
  int mem_fd;
  uint8_t* pwm_map[3];
  uint16_t frequency;

public:
  PWM(uint16_t frequency = 10000);

  bool init();
  void shutdown();

  enum {
    PWM0A = 0,
    PWM0B = 1,
    PWM1A = 2,
    PWM1B = 3,
    PWM2A = 4,
    PWM2B = 5,

    PWM_MAX
  };

  // Set the given PWM channel to the specified
  // value. 0 is off.
  void setChannel(int channel, int value = 0);

};

#endif // PWM_H
