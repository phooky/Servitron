#include <string>
#include <fstream>

bool writePath(std::string path, int value, bool hex) {
  std::ofstream outf;
  outf.open(path.c_str());
  if (hex) { outf << std::hex; }
  outf << value;
  outf.close();
  return true;
}
