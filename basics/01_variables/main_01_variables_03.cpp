#include <iostream>

int main()
{
    using namespace std;

    cout << 33 / 5 << endl;
    // 정수끼리의 연산은 정수로 취급하기 때문에 6.6이 아닌 그냥 6이 나옴.
    cout << (float)33 / 5 << endl;

}