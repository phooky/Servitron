#inlcude "pwm.h"
#include <unistd.h>

void main() {
  PWM pwm();
  pwm.init();
  for (int i = 0; i < 6; i++) {
    pwm.setChannel(i, i*1000);
  }
  sleep(60);
  pwm.shutdown();
}

  
