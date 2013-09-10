#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <fstream>

bool writePath(std::string path, int value, bool hex = true);

class LedOut {
public:
  const std::string m_name;
  LedOut(std::string& name);
  void set(int value);
  ~LedOut();
private:
  std::ofstream m_outf;
};

#endif // UTIL_H
