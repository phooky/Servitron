#include "servo.h"
#include "brake.h"
#include <iostream>

#define SERVO 1
int main() {
  // MoveBlock block(5.0,2.0,1.0,0.4,0.4);
  // float delta = 0.1;
  // float time = 0.0;

  // while (1) {
  //   float p, v, a;
  //   block.update(delta,p,v,a);
  //   time += delta;
  //   std::cout << time << "," << p << "," << v << "," << a << std::endl;
  // }

  PWM pwm;
  Quadrature q;
  Brake b;
  b.init();
  b.setBrake(false);
  pwm.init();
  Motor m(pwm);
  m.init();
  q.init();
  Servo servo(SERVO,q,m);
  servo.pid().setK(4,0.01,0.001);
  servo.setPoint(2000);
  for (int i = 0; i < 5000; i++) {
	  Report r = q.getNextReport();
          servo.update(r.state[SERVO].position);
	  std::cout << r.state[SERVO].position << std::endl;
  }
  m.setPower(SERVO,0);
  b.setBrake(true);
  q.shutdown();

}
