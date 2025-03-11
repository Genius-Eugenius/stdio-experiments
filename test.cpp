// Test working WO using IDE
#include "project.h"

using namespace std;

int
main(void)
{
    int num;

    num = (uint8_t)~1;
//    cout << bitset<18>(num) << endl;
    cout
        << setbase(8) << num << endl
        << setbase(10) << num << endl
        << setbase(16) << num << endl;

    cout << num << endl;
    return 0;
}
