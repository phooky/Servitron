#include "PID.h"

PID::PID() {
  init();
}

void PID::init() {
  kp = kd = ki = sum_e = prev_e = 0.0;
}

void PID::setK(float p, float d, float i) {
  kp = p; kd = d; ki = i;
}

float PID::step(float vs, float error) {
  float d = error - prev_e;
  sum_e += d;
  float rv = (kp * error) + (kd * d) + (ki * sum_e) + vs;
  prev_e = error;
  return rv;
}
