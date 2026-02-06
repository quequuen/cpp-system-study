#include <iostream>
#include <limits>

int main()
{
    using namespace std;

    bool b1 = true; // copy initialization
    bool b2(false); // direct initialization
    bool b3 { true }; // uniform initialization
    b3 = false;

    cout << std::boolalpha;
    // 기본적으로 cout은 bool 값을 0(false), 1(true)로 출력
    // boolalpha를 사용하면 true, false로 출력하게 됨.
    // 반대는 noboolalpha
    cout << !b3 << endl;
    cout << b1 << endl;

    char c1(65);

    cout << sizeof(unsigned char) << endl;
    cout << (int)std::numeric_limits<unsigned char>::max() << endl;
    cout << (int)std::numeric_limits<unsigned char>::min() << endl;
    cout << (int)std::numeric_limits<unsigned char>::lowest() << endl;

    char c2('A'); // 한 글자일 경우, ''로 감싸서 표현 가능

    cout << c1 << " " << int(c1)<< endl;
    cout << c2 << endl;
    // C 스타일 캐스팅
    cout << (char)65 << endl;
    // C++ 스타일 캐스팅
    cout << char(65) << endl;
    cout << static_cast<char>(65) << endl;
    cout << static_cast<int>('A') << endl;

    char ch(97);
    cout << ch << endl;
    cout << static_cast<int>(ch) << endl;
    cout << ch << endl;

    char c3;

    cin >> c3;
    cout << c3 << " " << static_cast<int>(c3) << endl;
    cin >> c3;
    cout << c3 << " " << static_cast<int>(c3) << endl;
    cin >> c3;
    cout << c3 << " " << static_cast<int>(c3) << endl;

    return 0;
}