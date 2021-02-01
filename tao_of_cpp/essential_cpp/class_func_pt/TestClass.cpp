#include <iostream>

using namespace std;

class Foo {
public:
	typedef void (Foo::*PtrType)(int);
	
    Foo() {
		pFuncArr = (PtrType*)malloc(sizeof(PtrType) * 2);
		pFuncArr[0] = &Foo::func1;
		pFuncArr[1] = &Foo::func2;
    }

	~Foo() {
		free(pFuncArr);
    }

	void DoTest() {
		for(int i = 0; i < 2; i++) {
			(this->*pFuncArr[i])(i+1);
		}
	}
private:
	PtrType *pFuncArr;
protected:
	void func1(int num)
	{
		cout << "This is func 1: "
			 << num
			 << endl;
	}
	
	void func2(int num)
	{
		cout << "This is func 1: "
			 << num
			 << endl;
	}
};

int main(int argc, char **argv) {
	Foo foo;
	foo.DoTest();
    return 0;
}
