#include <iostream>
#include <cmath>

int main()
{
    using namespace std;

    short s = 1; // 2 bites = 16 bits
    

    cout << sizeof(short) << endl;
    cout << std::pow(2, sizeof(short) * 8 - 1) - 1 << endl;
    // 첫번째 -1은 부호를 나타내는 비트 때문에 1 비트를 하나 빼준 것
    // 두번째 -1은 0을 표현하는 부분을 뺌
    return 0;
}