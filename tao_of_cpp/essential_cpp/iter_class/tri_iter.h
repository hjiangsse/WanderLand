#ifndef _TRI_ITERATOR_H_
#define _TRI_ITERATOR_H_

#include <iostream>

using namespace std;

class Triangular_iterator
{
public:
  Triangular_iterator(int index)
	: _index(index - 1)
  {
  }
  bool operator==(const Triangular_iterator& ) const;
  bool operator!=(const Triangular_iterator& ) const;
  int operator*() const;
  
  Triangular_iterator& operator++();     //prefix++
  Triangular_iterator operator++(int);   //posfix++
  
  void check_integrity() const;
private:
  int _index;
};

#endif
