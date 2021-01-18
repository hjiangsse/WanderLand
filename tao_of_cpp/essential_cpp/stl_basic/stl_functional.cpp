#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std;

template <typename elemType>
void display_vector(vector<elemType> &vec, ostream &os); 

int main() {
  int arr[] = {4,2,1,2,5,9};
  vector<int> ivec(arr, arr + 6);
  sort(ivec.begin(), ivec.end(), greater<int>());

  display_vector(ivec, cout);

  vector<int> res_vec;
  unique_copy(ivec.begin(), ivec.end(), back_inserter(res_vec));

  display_vector(res_vec, cout);

  copy(ivec.begin(), ivec.end(), inserter(res_vec, res_vec.end()));
  display_vector(res_vec, cout);
  return 0;
}

template <typename elemType>
void display_vector(vector<elemType> &vec, ostream &os) {
  typename vector<elemType>::iterator ibegin = vec.begin();
  typename vector<elemType>::iterator iend = vec.end();

  for(; ibegin != iend; ibegin++) {
	os << *ibegin << " ";
  }

  os << endl;
}
