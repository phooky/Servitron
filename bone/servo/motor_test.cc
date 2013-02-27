#include "pwm.h"
#include "motor.h"
#include "unistd.h"

int main() {
  PWM pwm;
  pwm.init();
  Motor m0(pwm, 1, 8, 9, "lcd_data2", "lcd_data3");
  m0.init();
  m0.setPower(5000);
  sleep(1);
  m0.setPower(0);
  sleep(1);
  m0.setPower(-5000);
  sleep(1);
  m0.setPower(0);
  m0.shutdown();
  pwm.shutdown();
}
