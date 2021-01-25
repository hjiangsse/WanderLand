#include "tri.h"
#include <algorithm>

using namespace std;

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

bool Triangular::is_elem(int value) {
  if(!_elems.size() ||
	 _elems[_elems.size() - 1] < value) {
	gen_elems_to_value(value);
  }

  vector<int>::iterator found_it;
  vector<int>::iterator end_it = _elems.end();

  found_it = find(_elems.begin(), end_it, value);
  return found_it != end_it;
}

void Triangular::gen_elems_to_value(int value) {
  int ix = _elems.size();
  if(!ix) {
	_elems.push_back(1);
	ix = 1;
  }

  while(_elems[ix - 1] < value && ix < _max_elems) {
	++ix;
	_elems.push_back(ix * (ix + 1) / 2);
  }

  if(ix == _max_elems) {
	cerr << value << " -- exceeds max size of "
	     << _max_elems << endl;
  }
}

void Triangular::gen_elements(int length) {
  if(length < 0 || length > _max_elems) {
    cout << "wrong lenth" << endl;
	return;
  }

  if(_elems.size() < length) {
	int ix = _elems.size()?_elems.size() + 1: 1;
	for(; ix <= length; ix++) {
	  _elems.push_back(ix*(ix+1)/2);
	}
  }
}
