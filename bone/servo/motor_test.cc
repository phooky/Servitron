#include "pwm.h"
#include "motor.h"
#include "unistd.h"

int main() {
  PWM pwm;
  Motor m0(pwm, 0, 6, 7, "lcd_data0", "lcd_data1");
  pwm.init();
  m0.init();
  m0.setPower(5000);
  sleep(1);
  m0.setPower(0);
  sleep(1);
  m0.setPower(-5000);
  sleep(1);
  m0.setPower(0);
  sleep(1);
  m0.shutdown();
  pwm.shutdown();
}
