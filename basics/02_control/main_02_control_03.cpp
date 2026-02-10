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

    // 비트 플래그

    const unsigned char opt0 = 1 << 0;
    const unsigned char opt1 = 1 << 1;
    const unsigned char opt2 = 1 << 2;
    const unsigned char opt3 = 1 << 3;

    // 아무것도 가지지 않은 상태: 00000000
    cout << bitset<8>(opt0) << endl;
    cout << bitset<8>(opt1) << endl;
    cout << bitset<8>(opt2) << endl;
    cout << bitset<8>(opt3) << endl;

    unsigned char flag = 0;
    cout << "No Status: " << bitset<8>(flag) << endl;

    // 상태 1 추가: 00000001
    flag |= opt0;
    cout << "Status 1: " << bitset<8>(flag) << endl;

    // 상태 2 추가: 00000010
    flag |= opt1;
    cout << "Status 2: " << bitset<8>(flag) << endl;

    // 상태 2 제거: 00000001
    flag &= ~opt1;
    cout << "Lost Status 2: " << bitset<8>(flag) << endl;

    // 상태 3 추가: 00000100
    flag |= opt2;
    cout << "Status 3: " << bitset<8>(flag) << endl;

    // 상태 4 추가: 00001000
    flag |= opt3;
    cout << "Status 4: " << bitset<8>(flag) << endl;

    // No Status 확인
    if ((flag & (opt0 | opt1 | opt2 | opt3)) == 0)
        cout << "No Status" << endl;

    // Status 1 보유 여부 확인
    if (flag & opt0)
        cout << "Has Status 1" << endl;

    // Status 2, 3를 모두 보유 할 시 4를 부여
    if ((flag & (opt1 | opt2)) == (opt1 | opt2))
        flag |= opt3;

    // 비트 마스크

    const unsigned int mask1 = 0xFF0000;
    const unsigned int mask2 = 0x00FF00;
    const unsigned int mask3 = 0x0000FF;

    cout << std::bitset<32>(mask1) << endl;
    cout << std::bitset<32>(mask2) << endl;
    cout << std::bitset<32>(mask3) << endl;

    unsigned int color = 0xA1B2C3;

    cout << "Color: " << bitset<32>(color) << endl;

    unsigned char red = (color & mask1) >> 16;
    unsigned char green = (color & mask2) >> 8;
    unsigned char blue = (color & mask3);

    cout << "Red: " << (int)red << endl;
    cout << "Green: " << (int)green << endl;
    cout << "Blue: " << (int)blue << endl;

    return 0;
}