#include <iostream>
#include "header_files/utils.h"

using namespace std;

int main()
{
    // 함수 없이 단순 계산
    cout << 1+2 << endl;
    cout << 3+4 << endl;
    cout << 5+6 << endl;

    //함수 사용 계산
    cout << addNumbers(1, 2) << endl;
    cout << addNumbers(3, 4) << endl;
    cout << addNumbers(5, 6) << endl;

    cout << multiplyNumbers(1, 2) << endl;
    cout << multiplyNumbers(3, 4) << endl;
    cout << multiplyNumbers(5, 6) << endl;

    cout << printHelloUser("World") << endl;
    printHelloWorld();

    int a, b;

    cin >> a >> b;
    cout << "Sum: " << addNumbers(a, b) << endl;
    cout << "Product: " << multiplyNumbers(a, b) << endl;




    return 0;
}