#include <iostream>
#include "TutorialConfig.h"

using namespace std;

int main(int argc, char **argv)
{
    cout << argv[0] << " Version " << Tutorial_VERSION_MAJSOR << "."
	 << Tutorial_VERSION_MINOR << endl;
    cout << "Usage: " << argv[0] << " number" << endl;

    const double inputValue = std::stod(argv[1]);
    cout << "Input Value: " << inputValue << endl;
    return 0;
}
