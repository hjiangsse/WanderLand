#include <vector>
#include <iostream>

using namespace std;

const int seq_cnt = 2;
extern const vector<int> *(*seq_funcs[seq_cnt])(int);

void display(const vector<int> &vec, ostream& os);
const vector<int> * square_seq(int size);
const vector<int> * fibon_seq(int size);


