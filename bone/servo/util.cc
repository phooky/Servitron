#include <string>
#include <fstream>

bool writePath(std::string path, int value) {
  std::ofstream outf;
  outf.open(path.c_str());
  outf << std::hex << value;
  outf.close();
  return true;
}
