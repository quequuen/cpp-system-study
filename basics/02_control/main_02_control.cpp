#include <iostream>

bool returnBool(int a, int b)
{
    return a > b;
}


int main()
{
    using namespace std;

    cout << boolalpha;

    cout << (true && true) << endl; 
    cout << (true && false) << endl;
    cout << (false && true) << endl;
    cout << (false && false) << endl;
    cout << (true || true) << endl;
    cout << (true || false) << endl;
    cout << (false || true) << endl;
    cout << (false || false) << endl;

    if (false)  // 한 줄일 때는 중괄호 생략 가능.
        cout << "This won't be printed." << endl;
    else 
        cout << "This will be printed." << endl;

    cout << returnBool(3, 5) << endl;
    cout << returnBool(7, 2) << endl;
}