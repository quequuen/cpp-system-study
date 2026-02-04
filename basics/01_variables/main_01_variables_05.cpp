#include <iostream>

int main()
{
    using namespace std;

    bool b1 = true; // copy initialization
    bool b2(false); // direct initialization
    bool b3 { true }; // uniform initialization
    b3 = false;

    cout << std::boolalpha;
    cout << b3 << endl;
    cout << b1 << endl;


    return 0;
}