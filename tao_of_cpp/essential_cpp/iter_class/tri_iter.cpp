#include "tri.h"
#include "tri_iter.h"

inline bool Triangular_iterator::operator==(const Triangular_iterator &rhs) const
{
  return _index == rhs._index;
}

inline bool Triangular_iterator::operator!=(const Triangular_iterator &rhs) const
{
  return !(*this == rhs);
}

inline int Triangular_iterator::operator*() const
{
  check_integrity();
  return Triangular::_elems[_index];
}

inline void Triangular_iterator::check_integrity() const
{
  if(_index >= Triangular::_max_elems) {
	cout << "iterator overflow" << endl;
	return;
  }

  if(_index >= Triangular::_elems.size()) {
	Triangular::gen_elements(_index + 1);
  }
}

inline Triangular_iterator& Triangular_iterator::operator++() {
  ++_index;
  check_integrity();
  return *this;
}

inline Triangular_iterator Triangular_iterator::operator++(int) {
  Triangular_iterator tmp = *this;
  ++_index;
  check_integrity();
  return tmp;
}
