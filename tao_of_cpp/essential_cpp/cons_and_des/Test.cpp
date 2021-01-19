#include <iostream>
#include "Triangular.h"

using namespace std;

void TellTriMsg(const Triangular &tri);

int main() {
  Triangular tri1;
  Triangular tri2(10);
  Triangular tri3(10, 4);
  {
	Matrix ma(10, 20);
  }
  Triangular tri4(tri3);
  cout << tri4.get_len() << endl;
  cout << tri4.get_beg_pos() << endl;

  Matrix ma1(10,30);
  Matrix ma2(ma1);
  TellTriMsg(tri3);
  return 0;
}

void TellTriMsg(const Triangular &tri) {
  cout << "The length: " << tri.get_len() << endl;
  cout << "The Begin Position: " << tri.get_beg_pos() << endl;
}
