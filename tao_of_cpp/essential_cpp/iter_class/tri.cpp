#include "tri.h"

vector<int> Triangular::_elems;

Triangular::Triangular(int len, int bp) {
  _length = len > 0 ? len : 1;
  _beg_pos = bp > 0 ? bp : 1;
  _next = _beg_pos - 1;
}

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

void Triangular::gen_elements(int length) {
  if(length > _length) {
    _length = length;
  }

  for(int ix = 1; ix <= _length; ix++) {
    _elems.push_back(ix*(ix +1)/2);
  }
}
