#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>

using namespace std;

template <class type, int dim>
class Point
{
public:
    Point() {
    }

    Point(type coords[dim]) {
	for(int i = 0; i < dim; i++) {
	    _coords[i] = coords[i];
	}
    }

    type& operator[](int i) {
	assert(i < dim && i >= 0);
	return _coords[i];
    }

    type operator[](int i) const {
	assert(i < dim && i >= 0);
	return _coords[i];
    }

    friend ostream& operator<<(ostream &os, const Point<type, dim> &pt)
    {
	os << "( ";
	for(int i = 0; i < dim - 1; i++) {
	    os << pt[i] << ", ";
	}
	os << pt[dim - 1];
	os << " )";
	return os;
    }
private:
    type _coords[dim];
};

int main(int argc, char **argv) {
    int init[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const Point< int, 10 > pt(init);
    cout << pt << endl;
    return 0;
}

