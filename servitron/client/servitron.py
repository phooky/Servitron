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
        self.s.settimeout(0.5)
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
            else:
                s = s + r

    def sendNTStr(self,s):
        self.s.send(s.encode('ascii'))
        self.s.send('\x00')
    
    def hello(self):
        msg = struct.pack('=BH', 0x01, CLIENT_VERSION)
        self.s.send(msg)
        self.sendNTStr(self.clientStr)
        (rspCode,srvVersion) = struct.unpack('=BH',self.s.recv(3))
        srvStr = self.recvNTStr()
        return(srvVersion,srvStr)
        
    def getStatus(self):
        axisFormat='=iiB'
        msg = struct.pack('=B', 0x02)
        self.s.send(msg)
        (rspCode,) = struct.unpack('=B',self.s.recv(1))
        a = [None]*6
        for i in range(6):
            a[i] = struct.unpack(axisFormat,self.s.recv(struct.calcsize(axisFormat)))
        return (a, struct.unpack('=B',self.s.recv(1)))

    def getQueueStatus(self):
        queueStatFmt = '=H'
        msg = struct.pack('=B', 0x03)
        self.s.send(msg)
        (rspCode,) = struct.unpack('=B',self.s.recv(1))
        qstat = struct.unpack(queueStatFmt,self.s.recv(struct.calcsize(queueStatFmt)))
        return qstat
        

            
            
        

