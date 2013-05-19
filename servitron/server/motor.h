#ifndef MOTOR_H
#define MOTOR_H

namespace motor {
  bool init();
  void shutdown();

  // Set the motor to the specified
  // power. 0 is off. Negative values are CCW, positive
  // are CW.
  void setPower(int channel, int value = 0);
};

#endif // MOTOR_H
