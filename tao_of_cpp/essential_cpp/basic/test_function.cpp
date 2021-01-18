#include <vector>
#include <iostream>

using namespace std;

void display(const vector<int> &vec, ostream& os=cout);
void swap(int &left, int &right);
void bubble_sort(vector<int> &vec);
const vector<int> * fibon_seq(int size);
const vector<int> * square_seq(int size);

int main() {
  /*
  int ia[8] = {8,34,3,13,1,21,5,2};
  vector<int> ivec(ia, ia+8);
  display(ivec);

  int lf = 10;
  int rf = 20;
  cout << "Before swap: "
       << "lf: " << lf
       << " rf: " << rf
       << endl;
  swap(lf, rf);
  cout << "After swap: "
       << "lf: " << lf
       << " rf: " << rf
       << endl;

  bubble_sort(ivec);
  cout << "After bubble sort: " << endl;
  display(ivec);
  
  const vector<int> *pvec = fibon_seq(10);
  display(*pvec);
  const vector<int> *pvec2 = fibon_seq(20);
  display(*pvec2);
  */
  
}

void display(const vector<int> &vec, ostream& os) {
  for(int ix = 0; ix < vec.size(); ix++) {
    os << vec[ix] << ' ';
  }
  os << endl;
}

void swap(int &left, int &right) {
  int tmp = left;
  left = right;
  right = tmp;
}

void bubble_sort(vector<int> &vec) {
  for(int ix = 0; ix < vec.size(); ix++) {
    for(int jx = ix + 1; jx < vec.size(); jx++) {
      if(vec[ix] > vec[jx]) {
	swap(vec[ix], vec[jx]);
      }
    } 
  }
}

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

  for(int ix = elems.size(); ix < size; ix++) {
    elems.push_back((ix + 1) * (ix + 1));
  }

  return &elems;
}
