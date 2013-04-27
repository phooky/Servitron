#include "brake.h"
#include "unistd.h"

int main() {
  Brake brake;
  brake.init();
  for (int i = 0; i < 10; i++) {
    brake.setBrake(false);
    sleep(2);
    brake.setBrake(true);
    sleep(1);
  }
  brake.shutdown();
}
