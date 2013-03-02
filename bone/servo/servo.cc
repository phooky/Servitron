#include "servo.h"
#include "math.h"
#include <iostream>

MoveBlock::MoveBlock(float x0i, float x1i, 
                     float maxVi, float ai, float di) :
  x0(x0i), x1(x1i), maxV(maxVi), a(ai), d(di), t(0.0)
{
  float deltap = x1i - x0i;
  bool invert = deltap < 0;
  if (invert) deltap = -deltap;

  float bangpoint = sqrt(2*deltap/(a*(1+(a/d))));
  if (bangpoint*a < maxV) {
    tav = tvd = bangpoint;
    tend = tav + (tav * a / d);
  } else {
    // cruising distance is deltap minus up and down ramps
    tav = maxV / a;
    float td = maxV / d;
    float cruisep = deltap - ( (tav * maxV / 2.0) + (td * maxV / 2.0));
    float tc = cruisep / maxV;
    tvd = tc + tav;
    tend = tvd + td;
  }  
  if (invert) {
    maxV = -maxV;
    a = -a;
  } else {
    d = -d;
  }
}

bool MoveBlock::update(float delta, float& po, float& vo, float& ao) {
  t = t+delta;
  if (t < tav) {
    ao = a;
    vo = a*t;
    po = x0 + a*t*t/2;
  } else if (t < tvd) {
    ao = 0;
    vo = maxV;
    po = x0 + a*tav*tav + (t-tav)*maxV;
  } else if (t < tend) {
    ao = d;
    vo = maxV + (d * (t-tvd));
    po = x0 + a*tav*tav + (tvd-tav)*maxV + (t-tvd)*d;
  } else {
    ao = 0;
    vo = 0;
    po = x1;
    return true;
  }
  return false;
}

Servo::Servo(int chi, Quadrature& qi, Motor& mi) : ch(chi), qi(q), mi(m) {
}

void Servo::setPoint(int32_t spi) {
  sp = spi;
}

float Servo::update(int32_t pv) {
  int32_t delta = sp - pv;
  float cv = posPID.step(0.0,delta);
  std::cout << "power "<<cv<<std::endl;
  m.setPower(ch,cv);
}



