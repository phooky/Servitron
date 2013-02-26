#ifndef MOTOR_H
#define MOTOR_H

#include "pwm.h"
#include <stdint.h>
#include <string>
class Motor {
private:
  PWM& pwm;
  
  uint8_t* gpioMap;
  int gpioFd;

  int pwmChannel;
  int pinA;
  int pinB;

  const std::string muxA, muxB;
public:
  Motor(PWM& pwm, int pwmChannel, int pinA, pin pinB, 
        const std::string muxA, const std::string muxB);

  bool init();
  void shutdown();

  // Set the motor to the specified
  // power. 0 is off. Negative values are CCW, positive
  // are CW.
  void setPower(int value = 0);
};

#endif // MOTOR_H
