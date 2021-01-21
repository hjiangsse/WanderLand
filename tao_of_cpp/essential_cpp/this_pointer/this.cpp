#include <iostream>
#include <vector>

using namespace std;

int arr[] = {1,3,4};
vector<int> init(arr, arr + 3);

class Point3D {
public:
  Point3D(int xp = 0, int yp = 0, int zp = 0)
	: x(xp), y(yp), z(zp)
  {
	
  }

  int tell_x() const { return x; }
  int tell_y() const { return y; }
  int tell_z() const { return z; }
private:
  int x;
  int y;
  int z;
};

class NumList {
public:
  static void tell_list() {
	cout << "hello" << endl;
	for(vector<int>::const_iterator it = _elems.begin(); it != _elems.end(); it++) {
	  cout << *it << endl;
	}
  }
private:
  static vector<int> _elems;
};

vector<int> NumList::_elems(arr, arr + 3);

int main() {
  Point3D p(1,2,3);
  cout << "x: " << p.tell_x()
	   << " y: " << p.tell_y()
	   << " z: " << p.tell_z() << endl; 

  NumList::tell_list();
  return 0;
}
