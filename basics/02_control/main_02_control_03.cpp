#include <iostream>
#include <bitset>

int main()
{
    using namespace std;

    unsigned char a = 5;  // 00000101

    cout << (int)a << endl;
    cout << bitset<4>(a) << endl;

    unsigned char b = a << 3; // 00101000

    cout << (int)b << endl;
    cout << bitset<8>(b) << endl;
    cout << bitset<8>(b << 3) << " " << (b << 3) << endl;
    cout << bitset<8>(~b) << " " << (~b) << endl;
    cout << bitset<8>(5 | 12) << " " << (5 | 12) << endl;

    return 0; 
}