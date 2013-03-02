#ifndef SERVO_H
#define SERVO_H

#include "pid.h"
#include "quadrature.h"
#include "motor.h"

// move block on a single axis
class MoveBlock {
  float x0, x1;
  float maxV;
  float a, d;

  float tav,tvd,tend;
  float t;
public:
  // velocity, acc, dec are all positive
  MoveBlock(float x0, float x1, float maxV, float a, float d);
  bool update(float delta, float& p, float& v, float& a);
};

//
// Some rough numbers:
// Motor PWM should be around the range of 1-2KHz.
// PID sampling:
// 10KHz for a loop
// 1KHz for v loop
// 100Hz for p loop
//

class Servo {
  const float deltaA = 1.0/10000;
  const float deltaV = 1.0/1000;
  const float deltaP = 1.0/100;

  PID posPID;
  Quadrature& q;
  Motor& m;
  int32_t sp;
  int ch;
public:
  Servo(int ch, Quadrature& q, Motor& m);
  PID& pid() { return posPID; }
  void setPoint(int32_t sp);
  void update(int32_t pv);
};


#endif // SERVO_H
