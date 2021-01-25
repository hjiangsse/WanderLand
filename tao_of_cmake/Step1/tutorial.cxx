#include <iostream>
#include "TutorialConfig.h"
#include <cmath>
#ifdef USE_MYMATH
#include "MathFunctions.h"
#endif

using namespace std;

int main(int argc, char **argv)
{
    cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
	 << Tutorial_VERSION_MINOR << endl;
    cout << "Usage: " << argv[0] << " number" << endl;

    const double inputValue = std::stod(argv[1]);
    cout << "Input Value: " << inputValue << endl;

    #ifdef USE_MYMATH
      const double outputValue = mysqrt(inputValue);
    #else
      const double outputValue = sqrt(inputValue);
    #endif
    
    cout << "OutputValue: " << outputValue << endl;

    return 0;
}
