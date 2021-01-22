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
  friend int Triangular_iterator::operator*() const;
  friend void Triangular_iterator::check_integrity() const;

  int length() const { return _length; }
  int beg_pos() const { return _beg_pos; }
  int elem(int pos) const;

  bool next(int &val);
  void next_reset() const { _next = _beg_pos - 1; }
public:
  static void gen_elements(int length);
private:
  int _max_elems;
  int _length;
  int _beg_pos;
  
  mutable int _next;
  static vector<int> _elems;
};

#endif
