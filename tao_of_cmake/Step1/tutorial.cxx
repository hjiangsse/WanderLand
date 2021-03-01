#include <iostream>
#include <cstdlib>
#include "TutorialConfig.h"
#ifdef USE_MYMATH
#include "MathFunctions.h"
#else
#include <cmath>
#endif

using namespace std;

int main(int argc, char **argv) {
    if(argc < 2) {
        cout << argv[0] << " Version: " << Tutorial_VERSION_MAJOR << "."
             << Tutorial_VERSION_MINOR << endl;
        cout << "Usage: " << argv[0] << " number" << endl;
        return 1;
    }

    const double inputValue = std::stod(argv[1]);
    cout << "The inputValue is: " << inputValue << endl;
#ifdef USE_MYMATH
    const double outputValue = mysqrt(inputValue);
#else
    const double outputValue = sqrt(inputValue);
#endif
    cout << "The outputValue is: " << outputValue << endl;
    cout << "Bye!" << endl;
    return 0;
}

