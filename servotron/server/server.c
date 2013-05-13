#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>

#include <string.h>
#include <iostream>

using namespace std;

#ifndef SOCKET_NAME
#define SOCKET_NAME "/var/run/servotron"
#endif

const char* socket_name = SOCKET_NAME;

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
      write(inSock,"GOODBYE\n",8);
      close(inSock);
    }
  }
  return 0;
}

int main(int argc, char*argv[]) {
  return startSocketServer(socket_name);
}
