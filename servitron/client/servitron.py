#!/usr/bin/env python

import struct
import socket

SOCKET_NAME='\x00/var/run/servotron'

CLIENT_VERSION=0x0001

RSP_OK = 0x80
RSP_ERR = 0x81

class Servitron:
    def __init__(self):
        self.s = socket.socket(socket.AF_UNIX)
        self.s.setTimeout(0.5)
        self.clientStr = 'Servitron Python client'

    def connect(self):
        self.s.connect(SOCKET_NAME)

    def close(self):
        self.s.close()

    def recvNTStr(self):
        s = ''
        while True:
            r = self.s.recv(1)
            if r == '\x00':
                return s
            s = s + r

    def hello(self):
        msg = struct.pack('BH', 0x01, CLIENT_VERSION)
        self.s.send(msg)
        self.s.send(self.clientStr)
        self.s.send(0)
        (rspCode,srvVersion) = struct.unpack('BH',self.s.recv(3))
        srvStr = self.recvNTStr()
        
        
            
        

