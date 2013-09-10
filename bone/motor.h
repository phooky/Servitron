#ifndef MOTOR_H
#define MOTOR_H

#include "util.h"

class MotorImpl;

class Motors {
public:
  Motors();
  ~Motors();
  void enable(bool en);
  // Set the motor to the specified
  // power. 0 is off. Negative values are CCW, positive
  // are CW.
  void setPower(int channel, int value = 0);
private:
  LedOut m_en;
  MotorImpl* m_impl[6];
};

#endif // MOTOR_H
