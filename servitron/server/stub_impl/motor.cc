#include "../motor.h"
#include <iostream>

using namespace std;

bool motor::init() {
  cout << "STUB: Initializing motor subsystem" << endl;
  return true;
}

void motor::shutdown() {
  cout << "STUB: Shut down motor subsystem" << endl;
}

void motor::setPower(int channel, int value) {
  cout << "STUB: setting motor channel "<<channel<<" to "<<value<<endl;
}

