#include "head.h"

const vector<int> *(*seq_funcs[seq_cnt])(int) =
{
 fibon_seq,
 square_seq
};

const vector<int> * fibon_seq(int size) {
  const int max_size = 1024;
  static vector<int> elems;

  if(size <= 0 || size > max_size) {
    cerr << "Invalid size: " << size << endl;
  }

  for(int ix = elems.size(); ix < size; ix++) {
    if(ix == 0 || ix == 1) {
      elems.push_back(1);
    }
    else {
      elems.push_back(elems[ix-1] + elems[ix - 2]);
    }
  }

  return &elems;
}

const vector<int> * square_seq(int size) {
  const int max_size = 1024;
  static vector<int> elems;

  if(size <= 0 || size > max_size) {
    cerr << "Invalid size: " << size << endl;
  }

  for(int ix = 0; ix < size; ix++) {
    elems.push_back((ix + 1) * (ix + 1));
  }

  return &elems;
}

void display(const vector<int> &vec, ostream& os) {
  for(int ix = 0; ix < vec.size(); ix++) {
    os << vec[ix] << ' ';
  }
  os << endl;
}
