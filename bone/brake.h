#ifndef BRAKE_H
#define BRAKE_H

#include <stdint.h>

class Brake {
private:
  uint8_t* gpioMap;
  int gpioFd;
public:
  Brake();

  bool init();
  void shutdown();

  // Brake is "on" by default
  void setBrake(bool on);
};

#endif // BRAKE_H
