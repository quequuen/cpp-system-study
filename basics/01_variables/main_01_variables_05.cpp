#include <iostream>

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


    return 0;
}