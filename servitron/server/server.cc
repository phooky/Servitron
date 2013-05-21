#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>

#include <string.h>
#include <iostream>

#include "../include/servitron_cmd.h"

using namespace std;
using namespace servitron;

#ifndef SOCKET_NAME
#define SOCKET_NAME "/var/run/servotron"
#endif

#ifndef SERVER_VERSION
#define SERVER_VERSION 0x0001
#endif

#ifndef SERVER_MESSAGE
#define SERVER_MESSAGE "Servitron server debug build"
#endif

const char* socket_name = SOCKET_NAME;
const uint16_t server_version = SERVER_VERSION;
const std::string server_msg(SERVER_MESSAGE);

bool processCommand(int sock);

int startSocketServer(const char* sockName) {
  unsigned int listenSock = socket(AF_UNIX, SOCK_STREAM, 0);
  struct sockaddr_un listenSockaddr;
  listenSockaddr.sun_family = AF_UNIX;
  // Set up abstract socket namespace; Linux-only but saves us from
  // mucking around with unlink() and multiple servers running
  // simultaneously.
  strcpy(listenSockaddr.sun_path+1,sockName);
  listenSockaddr.sun_path[0]='\0';
  size_t len = sizeof(listenSockaddr.sun_family) + 1 + strlen(sockName);
  if (bind(listenSock, (struct sockaddr*)&listenSockaddr, len) == -1) {
    cerr << "Could not bind " << sockName << ": " <<strerror(errno) <<endl;
    return -1;
  }
  if (listen(listenSock,2) == -1) {
    cerr << "Could not listen on " << sockName << ": " <<strerror(errno) <<endl;
    return -1;
  }
  while(1) {
    // Accept one client at a time.
    struct sockaddr_un inSockaddr;
    socklen_t len = sizeof(inSockaddr);
    int inSock = accept(listenSock, (struct sockaddr*)&inSockaddr, &len);
    if (inSock == -1) {
      cerr << "Bad accept on " << sockName << ": " <<strerror(errno) <<endl;
    } else {
      while(processCommand(inSock));
      close(inSock);
    }
  }
  return 0;
}

// FIXME: limited-length buffer!
std::string recvNTStr(int sock) {
  const size_t buflen = 256;
  char buf[buflen];
  size_t idx = 0;
  char c;
  while (recv(sock, &c, 1, 0) == 1 && c != '\0') {
    buf[idx++] = c;
    if (idx >= buflen) { idx = buflen - 1; }
  }
  buf[idx] = 0;
  return string(buf);
}

void sendNTStr(int sock, const std::string& s) {
  send(sock, s.c_str(), s.size(), 0);
  const char null = 0;
  send(sock, &null, 1, 0);
}

bool handleHello(int sock) {
  uint16_t clientVersion;
  recv(sock,&clientVersion,sizeof(clientVersion),0);
  std::string s = recvNTStr(sock);
  cout << "Got hello from version "<<clientVersion<<", message "<<s<<endl;
  send(sock,&RspOK,1,0);
  send(sock,&server_version,sizeof(server_version),0);
  sendNTStr(sock,server_msg);
  return true;
}

bool handleMechStatus(int sock) {
  MechStatusRsp rsp;
  // Fill mechanical status response
  for (int i =0; i < 6; i++) {
    rsp.axis[i].position = i;
    rsp.axis[i].velocity = -i;
    rsp.axis[i].flags = 100;
  }
  send(sock,&RspOK,1,0);
  send(sock,&rsp,sizeof(rsp),0);
  return true;
}

bool handleQueueStatus(int sock) {
  QueueStatusRsp rsp;
  // Fill queue status response
  rsp.remainingMoves = 0;
  send(sock,&RspOK,1,0);
  send(sock,&rsp,sizeof(rsp),0);
  return true;
}

bool processCommand(int sock) {
  uint8_t cmd;
  ssize_t sz = recv(sock, &cmd, 1, 0);
  if (sz == 1) {
    // process command
    switch(cmd) {
    case Hello:
      return handleHello(sock);
    case MechStatus:
      return handleMechStatus(sock);
    case QueueStatus:
      return handleQueueStatus(sock);
    default:
      break;
    }
  } else {
    return false; // orderly shutdown or error
  }
  return true;
}

int main(int argc, char*argv[]) {
  return startSocketServer(socket_name);
}
