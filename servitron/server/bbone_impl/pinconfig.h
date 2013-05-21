#ifndef PINCONFIG_H
#define PINCONFIG_H

#include <stdint.h>


// Pin configuration for the Servotron Six Version Zero / BeagleBone A5
typedef struct {
  // All quadrature input pins refer to GPIO Port 1.
  uint8_t quadA;
  uint8_t quadB;
  uint8_t quadIdx;
  // All motor output pins refer to GPIO Port 2.
  uint8_t motorA;
  uint8_t motorB;
  // The motor PWM pin refers to the channel in the PWM subsystem.
  uint8_t motorPWM;
} ServoPinConfig;

const uint8_t servoCount = 6;
const ServoPinConfig servoConfig[servoCount] = {
  { 6, 7, 2, 6, 7, 0 },       // servo 0
  { 3, 13, 12, 8, 9, 1 },     // servo 1
  { 15, 14, 31, 10, 11, 2 },  // servo 2
  { 30, 5, 4, 12, 13, 3 },    // servo 3
  { 1, 0, 29, 23, 25, 5 },    // servo 4
  { 28, 16, 17, 22, 24, 4 },  // servo 5
};

// The brake is on GPIO Port 0
const uint8_t BrakePinConfig = 26;

#define QUAD_STATE_BASE 0x00
#define CYCLE_COUNT_BASE 0xfc
#define REPORT_BASE 0x100

#endif // PINCONFIG_H
