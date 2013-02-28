#include "pwm.h"
#include "motor.h"
#include "unistd.h"

int main() {
  PWM pwm;
  pwm.init();
  Motor m0(pwm);
  m0.init();
  m0.setPower(1,5000);
  sleep(10);
  //m0.setPower(1,0);
  //sleep(1);
  m0.setPower(1,-5000);
  sleep(10);
  m0.setPower(1,0);
  m0.shutdown();
  pwm.shutdown();
}
