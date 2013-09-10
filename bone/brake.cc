#include <assert.h>
#include <unistd.h>
#include <stdexcept>
#include "config.h"
#include "brake.h"

// Brake is on port 0, pin 26
std::string outputPinName = "servitron:brake";


Brake::Brake() : m_brake_gpio(outputPinName) {}

bool Brake::init() {
  m_brake_gpio.set(1);
  return true;
}

void Brake::shutdown() {
  m_brake_gpio.set(1);
}

void Brake::setBrake(bool on) {
  if (!on) {
    m_brake_gpio.set(0);
  } else {
    m_brake_gpio.set(1);
  }
}

