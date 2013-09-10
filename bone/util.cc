#include "util.h"

bool writePath(std::string path, int value, bool hex) {
  std::ofstream outf;
  outf.open(path.c_str());
  if (hex) { outf << std::hex; }
  outf << value;
  outf.close();
  return true;
}

const std::string led_prefix = "/sys/class/leds/";
const std::string led_suffix = "/brightness";

LedOut::LedOut(std::string& name) : m_name(name) {
  std::string full_name = led_prefix + name + led_suffix;
  m_outf.open(full_name.c_str());
}

void LedOut::set(int value) {
  m_outf << value << std::endl;
}

LedOut::~LedOut() {
  m_outf.close();
}

