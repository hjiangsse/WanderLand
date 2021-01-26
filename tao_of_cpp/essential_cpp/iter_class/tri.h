#ifndef _TRIANGULAR_H_
#define _TRIANGULAR_H_ 1

#include <vector>
#include "tri_iter.h"

using namespace std;

class Triangular
{
public:
  Triangular(int len = 1, int bp = 1);
  
  typedef Triangular_iterator iterator;

  Triangular_iterator begin() const {
	return Triangular_iterator(_beg_pos);
  }

  Triangular_iterator end() const {
	return Triangular_iterator(_beg_pos + _length);
  }
  
  friend int Triangular_iterator::operator*() const;
  friend void Triangular_iterator::check_integrity() const;

  int length() const { return _length; }
  int beg_pos() const { return _beg_pos; }
  int elem(int pos) const;

  bool next(int &val);
  void next_reset() { _next = _beg_pos - 1; }
public:
  static bool is_elem(int value);
  static void gen_elements(int length);
  static void gen_elems_to_value(int value);
private:
  int _length;
  int _beg_pos;
  int _next;

  static const int _max_elems = 1024;
  static vector<int> _elems;
};

#endif
