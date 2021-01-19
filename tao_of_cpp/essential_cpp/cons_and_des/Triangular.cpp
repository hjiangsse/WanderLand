#include "Triangular.h"

Triangular::Triangular(int len, int bp)
  : _name("Triangular")
{
  _length = len;
  _beg_pos = bp;
  _next = _beg_pos - 1;
}
