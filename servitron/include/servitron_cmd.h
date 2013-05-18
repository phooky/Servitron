#ifndef SERVITRON_CMD_H
#define SERVITRON_CMD_H

#include <stdint.h>
// This defines the command structures for servitron 6.
namespace servitron {
  typedef uint8_t CommandCode;

  const CommandCode Hello = 0x01;

  typedef struct {
    uint16_t clientVersion;
    char* clientStr;
  } HelloCmd;

  typedef struct {
    uint16_t serverVersion;
    char* serverStr;
  } HelloRsp;

  const CommandCode MechStatus = 0x02;

  typedef struct {
    int32_t position;
    int32_t velocity;
  } MechAxisStatus;

  typedef struct {
    MechAxisStatus axis[6];
  } MechStatusRsp;

  const CommandCode QueueStatus = 0x03;
  
  typedef struct {
    int16_t remainingModes;
  } QueueStatusRsp;
};

#endif // SERVITRON_CMD_H
