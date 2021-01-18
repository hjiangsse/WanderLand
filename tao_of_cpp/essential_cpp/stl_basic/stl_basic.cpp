#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename elemType>
void display_vector(vector<elemType> &vec, ostream &os);

template <typename IteratorType, typename elemType>
IteratorType
raw_find(IteratorType first, IteratorType last, const elemType &value);

class IsEven {
public:
  bool operator()(const int &i) {
	return i % 2 == 0;
  }
};

vector<int> filter_vec(vector<int> &vec, int filter_value, bool (*pred)(int, int));
bool is_less_than(int left, int right);

int count_occurs(const vector<int> &vec, int val);

int main() {
  /*
  const char* cs[] = {"foo", "bar", "var"};
  vector<string> vs(cs, cs + 3);

  int is[] = {1234,3214,4321};
  vector<int> vi(is, is+3);

  for(vector<string>::iterator iter = vs.begin(); iter != vs.end(); iter++) {
	cout << "(" << iter->size() << ") " << *iter << endl;
  }

  for(vector<string>::const_iterator citer = vs.begin(); citer != vs.end(); citer++) {
	cout << *citer << endl;
	}

  display_vector(vs, cout);
  display_vector(vi, cout);

  vector<string>::iterator svec_begin = vs.begin();
  vector<string>::iterator svec_end = vs.end();
  if(raw_find(svec_begin, svec_end, "bar") != svec_end) {
	cout << "get the element!" << endl;
  }

  vector<int> ivec{7,2,3,1,5};
  vector<int>::iterator it = find_if(ivec.begin(), ivec.end(), IsEven());
  if(it != ivec.end()) {
	cout << *it << endl;
  }
  */
  int iarr[] = {9,3,1,3,8,5};
  vector<int> ivec(iarr, iarr + 6);
  vector<int> in_vec(ivec.size());
  copy(ivec.begin(), ivec.end(), in_vec.begin());

  //sort the copyed vector
  sort(in_vec.begin(), in_vec.end());
  display_vector(in_vec, cout);

  //do binary search in the sorted vector
  if(binary_search(in_vec.begin(), in_vec.end(), 3)) {
	cout << "Find the element in the vector" << endl;
  }

  vector<int> less_than_6 = filter_vec(ivec, 6, is_less_than);
  display_vector(less_than_6, cout);

  int cnt = count_occurs(ivec, 3);
  cout << "3 occurs: " << cnt << endl;
}

bool is_less_than(int left, int right) {
  if(left < right) {
	return true;
  }
  return false;
}

int count_occurs(const vector<int> &vec, int val) {
  vector<int>::const_iterator iter = vec.begin();
  int occurs_cnt = 0;
  while((iter = find(iter, vec.end(), val)) != vec.end()) {
	iter++;
	occurs_cnt++;
  }
  return occurs_cnt;
}

vector<int> filter_vec(vector<int> &vec, int filter_value, bool (*pred)(int, int))
{
  vector<int> res;
  for(vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++) {
	if(pred(*iter, filter_value)) {
	  res.push_back(*iter);
	}
  }
  return res;
}

template <typename elemType>
void display_vector(vector<elemType> &vec, ostream &os) {
  typename vector<elemType>::iterator ibegin = vec.begin();
  typename vector<elemType>::iterator iend = vec.end();

  for(; ibegin != iend; ibegin++) {
	os << *ibegin << endl;
  }
}

template <typename IteratorType, typename elemType>
IteratorType
raw_find(IteratorType first, IteratorType last, const elemType &value)
{
  for(; first != last; ++first) {
	if(value == *first) {
	  return first;
	}
  }

  return last;
}


