#ifndef QUADRATURE_H
#define QUADRATURE_H

#include <stdint.h>

typedef struct {
  int32_t position;
  uint8_t state;
  uint8_t pinA;
  uint8_t pinB;
  uint8_t pinIdx;
  uint16_t errors;
} __attribute__((packed)) QuadState;

typedef struct {
  QuadState state[6];
} __attribute__((packed)) Report;

class Quadrature {
private:
  uint8_t* pru_data_map;
  void initChannel(uint8_t ch, uint8_t a, uint8_t b, uint8_t idx);
public:
  Quadrature();
  void init();
  // Block until report signal recieved.
  // (how do we signal missed reports?)
  Report getNextReport();
  void shutdown();
};

#endif // QUADRATURE_H
