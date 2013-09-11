#include "pid.h"
#include <iostream>

PID::PID() {
  init();
}

void PID::init() {
  kp = kd = ki = sum_e = prev_e = 0.0;
}

void PID::setK(float p, float i, float d) {
  kp = p; kd = d; ki = i;
}

float PID::step(float vs, float error) {
  float d = error - prev_e;
  //if (error < 500 && error > -500)
  	sum_e += error;
  std::cout << "sum-e "<<sum_e<<std::endl;
  float rv = (kp * error) + (kd * d) + (ki * sum_e) + vs;
  prev_e = error;
  return rv;
}

