#ifndef BRAKE_H
#define BRAKE_H

#include <stdint.h>
#include "util.h"

class Brake {
private:
  LedOut m_brake_gpio;
public:
  Brake();

  bool init();
  void shutdown();

  // Brake is "on" by default
  void setBrake(bool on);
};

#endif // BRAKE_H
