Servotron Six
=============

Servotron Six is a six-axis DC servo control board initially developed to support PUMA robot arms and their cousins. It presumes that each servo consists of a DC gearmotor, a quadrature encoder, and optionally an index channel. It uses a BeagleBone A5 or greater to control the system and is designed so that your application can run directly on the BeagleBone.

It has not yet been tested with the new BeagleBone Black.

Hardware
--------

The board is designed to run off a 24V power supply. A switching supply provides 5V to the logic chips and the BeagleBone. Each servo channel is driven by a VNH3SP30 which can provide a peak of ~20A.

The hardware design files are in the "electronics/six_axis_board" directory. The hardware is licenced under the CERN Open Hardware License v1.1.

Software
--------

The software which runs on the BeagleBone is in the "servotron" directory.
