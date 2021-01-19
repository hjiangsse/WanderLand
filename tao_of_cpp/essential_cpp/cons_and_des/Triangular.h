#include <string>
#include <iostream>

using namespace std;

class Triangular {
 public:
  Triangular(int len = 1, int bp = 1);
  int get_len() const { return _length; }
  int get_beg_pos() const { return _beg_pos; }
  int get_next() const { return _next++; }
 private:
  string _name;
  int _length;
  int _beg_pos;
  int _next;
};

class Matrix {
 public:
  Matrix(int row, int col)
    : _row(row), _col(col)
    {
      _pmat = new double[ row * col ];
      cout << "allocate "
           << row * col
           << "int spaces"
           << endl;
    }

  Matrix(const Matrix& rhs)
    : _row(rhs.get_row()), _col(rhs.get_col())
  {
    _pmat = new double[_row * _col];

    for(int i = 0; i < _row * _col; i++) {
      _pmat[i] = rhs._pmat[i];
    }
  }
  
  ~Matrix() {
    delete [] _pmat;
    cout << "free all the allocated" << endl;
  }

  int get_row() const { return _row; }
  int get_col() const { return _col; }
 private:
  int _row, _col;
  double* _pmat;
};
