#include "pwm.h"
#include <unistd.h>

int main() {
  PWM pwm;
  pwm.init();
  for (int i = 0; i < 6; i++) {
    pwm.setChannel(i, i*10000);
  } 
  sleep(10);
  pwm.shutdown();
  return 0;
}

  
