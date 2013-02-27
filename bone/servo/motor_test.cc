#include "pwm.h"
#include "motor.h"
#include "unistd.h"

int main() {
  PWM pwm;
  pwm.init();
  sleep(1);
  Motor m0(pwm, 1, 6, 7, "lcd_data0", "lcd_data1");
  m0.init();
  m0.setPower(3000);
  sleep(1);
  m0.setPower(0);
  sleep(1);
  m0.setPower(-3000);
  sleep(1);
  m0.setPower(0);
  sleep(1);
  m0.shutdown();
  pwm.shutdown();
}
