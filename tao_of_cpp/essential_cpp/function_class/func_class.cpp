#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class LessThan {
public:
    LessThan(int val) : _val(val){ }
    ~LessThan() {}

	int comp_val() const { return _val; }
	void comp_val(int nval) { _val = nval; }

	bool operator()(int _value) const;
private:
	int _val;
};

//is the parameter less than the base value?
inline bool LessThan::
operator()(int _value) const {
	return _value < _val;
}

int count_less_than(const vector<int> &vec, int comp) {
	LessThan lt(comp);

	int count = 0;
	for(int ix = 0; ix < vec.size(); ix++) {
		if(lt(vec[ix]))
			++count;
	}

	return count;
}

void print_less_than(const vector<int> &vec, int comp, ostream &os = cout) {
	LessThan lt(comp);

	vector<int>::const_iterator iter = vec.begin();
	vector<int>::const_iterator iter_end = vec.end();

	os << "element less than " << lt.comp_val() << endl;
	while((iter = find_if(iter, iter_end, lt)) != iter_end) {
		os << *iter << ' ';
		++iter;
	}
}

int main(int argc, char **argv) {
	int ia[16] = { 17, 12, 44, 9, 18, 45, 6, 14,
				   23, 67, 9, 0, 27, 55, 8, 16 };
	vector<int> vec(ia, ia + 16);
	int comp_val = 20;

	cout << "Number of elements less than "
		 << comp_val << " are "
		 << count_less_than(vec, comp_val) << endl;
	print_less_than(vec, comp_val);
	cout << endl;
    return 0;
}
