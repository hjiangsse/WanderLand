#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

//define a functional class
class TellMessage
{
public:
  void operator () (int a, int b) {
    cout << "Title: " << a << endl;
    cout << "Message: "<< b << endl;
  }
};

template <typename InputIterator, typename OutputIterator,
          typename ElemType, typename Comp>
OutputIterator
filter(InputIterator first, InputIterator last,
       OutputIterator at, const ElemType &val, Comp pred)
{
  while ((first = find_if(first, last, bind2nd(pred, val))) != last) {
    cout << "Found value: " << *first << endl;
    *at++ = *first++;
  }
  return at;
}

int main() {
  /*
  plus<int> plus_int = plus<int>();
  cout << plus_int(1,2) << endl;
  plus<double> plus_double = plus<double>();
  cout << plus_double(1.0, 2.3) <<endl;
  minus<int> minus_int = minus<int>();
  cout << minus_int(1,2) << endl;

  int iarr[] = {1,3,2,6,4};
  vector<int> ivec(iarr, iarr + 5);

  sort(ivec.begin(), ivec.end(), less<int>());
  
  if(binary_search(ivec.begin(), ivec.end(), 2, less<int>())) {
    cout << "Find it!" << endl;
  }

  TellMessage tm = TellMessage();
  tm(1, 2);
  
  bind1st(tm, 10)(20);
  */

  int iarr[] = {1,3,2,6,4};
  vector<int> ivec(iarr, iarr + 5);
  vector<int> res_vec(ivec.size());

  filter(ivec.begin(), ivec.end(), res_vec.begin(), 5 , less<int>());
  
  return 0;
}
