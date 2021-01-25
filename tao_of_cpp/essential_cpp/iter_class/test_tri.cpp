#include <iostream>
#include "tri.h"
#include "tri_iter.h"

using namespace std;

int main(int argc, char **argv) {
  Triangular tri(10, 1);
  Triangular::iterator it = tri.begin();
  Triangular::iterator end_it = tri.end();

  cout << tri.length() << endl;
  while(it != end_it) {
	cout << *it << endl;
	++it;
  }
  return 0;
}
