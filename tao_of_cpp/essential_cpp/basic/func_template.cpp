#include <iostream>
#include <vector>

using namespace std;

template <typename elemType>
void display_message(const string &msg, const vector<elemType> &vec);

int main() {
  static const int iarr[] = {16,2,77,29};
  vector<int> ivec(iarr, iarr + sizeof(iarr) / sizeof(iarr[0]));

  static const string sarr[] = {"hjiang", "heng", "zhang"};
  vector<string> svec(sarr, sarr + sizeof(sarr) / sizeof(sarr[0]));

  display_message("This is vector1: ", ivec);
  display_message("This is vector2: ", svec);

  return 0;
}

template <typename elemType>
void display_message(const string &msg, const vector<elemType> &vec)
{
  cout << msg;
  for(int ix = 0; ix < vec.size(); ix++)
  {
    elemType t = vec[ix];
    cout << t << ' ';
  }
  cout << endl;
}
