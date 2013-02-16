#!/usr/bin/python

# all measurements in mm
padWidth = 0.68
padHeight = 3.0
pitch = 1.0
pinNum = 1
tstopOffset = 0.1

def pin(xc,yc,dx=padWidth,dy=padHeight):
    global pinNum
    x = xc
    y = yc
    t = '<smd name="P${0}" x="{1}" y="{2}" dx="{3}" dy="{4}" layer="1"/>'
    print(t.format(pinNum,x,y,dx,dy))
    pinNum = pinNum + 1

def pinRow(yc,count,inc=1):
    # centered pin row
    offset = -inc * (((count-1)*pitch)/2)
    xc = offset
    for _ in range(count):
        pin(xc,yc)
        xc = xc + inc*pitch

def thermal(x,y,dx,dy):
    r = '<rectangle x1="{0}" y1="{1}" x2="{2}" y2="{3}" layer="{4}"/>'
    print(r.format(x,y,x+dx,y+dy,1))
    print(r.format(x-tstopOffset,y-tstopOffset,x+dx+tstopOffset,y+dy+tstopOffset,29))

tpinNum = 1
def thermalPin(x,y,dx,dy):
    global tpinNum
    cx = x + dx/2.0
    cy = y + dy/2.0
    t = '<smd name="T${0}" x="{1}" y="{2}" dx="{3}" dy="{4}" layer="1"/>'
    print(t.format(tpinNum,cx,cy,dx,dy))
    tpinNum = tpinNum + 1

print('<package name="MULTIPOWER-SO-30">')
pinRow(-10.0,15)
pinRow(10.0,15,-1)
thermalPin(-7.28,.425,6.23,5.25)
thermalPin(1.05,.425,6.23,5.25)
thermalPin(-5.15,-5.675,10.3,5.25)
print('</package>')
