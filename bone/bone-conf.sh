#!/bin/sh
systemctl stop graphical.target
systemctl disable graphical.target
systemctl stop storage-gadget-init.service
systemctl disable storage-gadget-init.service
echo nameserver 192.168.1.1 >/etc/resolv.conf
route add default gw 192.168.7.1
