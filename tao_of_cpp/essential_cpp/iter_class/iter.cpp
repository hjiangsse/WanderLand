#include <iostream>
#include <vector>
#include "tri_iter.h"

using namespace std;

class Triangular
{
public:
  typedef Triangular_iterator iterator;
  friend int Triangular_iterator::operator*() const;
  friend void Triangular_iterator::check_integrity() const;

  int length() const { return _length; }
  int beg_pos() const { return _beg_pos; }
  int elem(int pos) const;

  bool next(int &val);
  void next_reset() const { _next = _beg_pos - 1; }
private:
  int _max_elems;
  int _length;
  int _beg_pos;
  mutable int _next;
  static vector<int> _elems;
};

vector<int> Triangular::_elems;

int Triangular::elem(int pos) const {
  return _elems[pos - 1];
}

bool Triangular::next(int &value) {
  if(_next < _beg_pos + _length - 1) {
	value = _elems[_next++];
	return true;
  }
  return false;
}

int main() {
  return 0;
}
