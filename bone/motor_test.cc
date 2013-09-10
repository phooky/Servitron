#include "motor.h"
#include <unistd.h>
#include <stdlib.h>

void testMotor(int idx,Motors& m) {
  m.setPower(idx,5000);
  sleep(1);
  m.setPower(idx,-5000);
  sleep(1);
  m.setPower(idx,0);
}

int main(int argc, char** argv) {
  Motors m;
  if (argc < 2) {
    testMotor(0,m);
  } else {
    for (int i = 1; i < argc; i++) {
      int idx = atoi(argv[i]);
      if (idx >= 0 && idx < 6) {
        testMotor(idx,m);
      }
    }
  }
}
