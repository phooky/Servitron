#include "quadrature.h"
#include <iostream>
using namespace std;
int main() {
  Quadrature q;
  q.init();

  for (int i = 0; i < 10000; i++) {
	  Report r = q.getNextReport();
	  cout << "Report: [";
          cout << r.cycles;
          cout << "]: ";
	  for (int j = 0; j < 6; j++) {
		  cout << j << ":" << r.channel[j].position << " ";
	  }
	  cout << endl;
  }
  q.shutdown();
}

