#include <iostream>

using namespace std;

class num_sequence {
public:  
    inline virtual ~num_sequence() {};

    virtual int elem(int pos) const = 0;         //pure virtual function
    virtual const char* what_am_i() const = 0;
    virtual ostream& print(ostream& os = cout) const = 0;
    static int max_elems() { return _max_items; }

    virtual int length() const = 0;
    virtual int beg_pos() const = 0;

    friend ostream& operator<<(ostream& os, const num_sequence &ns);
protected:
    virtual void gen_elems(int pos) const = 0;
    bool check_integrity(int pos) const;
    const static int _max_items = 1024;
};

bool num_sequence::check_integrity(int pos) const {
    if(pos <= 0 || pos > _max_items) {
	cerr << "!! invalid position: " << pos
	     << " can not hold request!\n";
	return false;
    }

    return true;
}

ostream& operator<<(ostream& os, const num_sequence &ns)
{
    return ns.print(os);
}
