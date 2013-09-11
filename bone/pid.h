#ifndef PID_H
#define PID_H

class PID {
  float kp, ki, kd;
  float sum_e;
  float prev_e;
public:
  PID();
  void init();
  void setK(float kp, float ki, float kd);
  float step(float vs, float error);
};


#endif // PID_H
