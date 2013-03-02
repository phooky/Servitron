#include "quadrature.h"
#include <iostream>
using namespace std;
int main() {
  Quadrature q;
	cout << "starting." << endl;
  q.start();

  for (int i = 0; i < 10000; i++) {
	  Report r = q.getNextReport();
	  cout << "Report: ";
	  for (int j = 0; j < 6; j++) {
		  cout << j << ":" << r.state[j].position << " ";
	  }
	  cout << endl;
  }
  cout << "stopping." << endl;
  q.stop();
}

