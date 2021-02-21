#include "Fibonacci.h"
#include <typeinfo>

int main(int argc, char **argv) {
    Fibonacci fib;
    cout << "Fib: beginning at element 1 for 1 elements: "
	 << fib << endl;

    Fibonacci fib2(16);
    cout << "Fib: beginning at element 1 for 16 elements: "
	 << fib2 << endl;

    Fibonacci fib3(8, 12);
    cout << "Fib: beginning at element 12 for 8 elements: "
	 << fib3 << endl;

    cout << typeid(fib3).name() << endl;
    return 0;
}
