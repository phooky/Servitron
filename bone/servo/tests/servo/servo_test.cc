#include "servo.h"
#include "brake.h"
#include <iostream>

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
  b.setBrake(true);
  pwm.init();
  Motor m(pwm);
  m.init();
  q.init();
  Servo servo(4,q,m);
  servo.pid().setK(4,0.01,0);
  servo.setPoint(5000);
  for (int i = 0; i < 5000; i++) {
	  Report r = q.getNextReport();
          servo.update(r.state[4].position);
	  std::cout << r.state[4].position << std::endl;
  }
  m.setPower(4,0);
  q.shutdown();

}
