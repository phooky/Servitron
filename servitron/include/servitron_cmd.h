#ifndef SERVITRON_CMD_H
#define SERVITRON_CMD_H

#include <stdint.h>
// This defines the command structures for servitron 6.
namespace servitron {
  typedef uint8_t CmdCode;
  typedef uint8_t RspCode;

  const RspCode RspOK = 0x80;
  const RspCode RspError = 0x81;

  const CmdCode Hello = 0x01;

  typedef struct {
    uint16_t clientVersion;
    char* clientStr;
  } HelloCmd;

  typedef struct {
    uint16_t serverVersion;
    char* serverStr;
  } HelloRsp;

  const CmdCode MechStatus = 0x02;

  typedef struct {
    int32_t position;
    int32_t velocity;
  } MechAxisStatus;

  typedef struct {
    MechAxisStatus axis[6];
  } MechStatusRsp;

  const CmdCode QueueStatus = 0x03;
  
  typedef struct {
    int16_t remainingModes;
  } QueueStatusRsp;
};

#endif // SERVITRON_CMD_H
