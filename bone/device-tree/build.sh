#!/bin/bash
dtc -O dtb -o cape-servitron-00A0.dtbo -b o -@ cape-servitron-six-00A0.dts 
cp cape-servitron-00A0.dtbo /lib/firmware/BB-SERVITRON-SIX-00A0.dtbo
