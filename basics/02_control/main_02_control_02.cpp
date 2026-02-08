#include <iostream>

int addNumbers(int a, int b)
{
    return a + b;
}

int main()
{
    using namespace std;

    int one = 1;

    cout << one << endl;
    cout << one-- + 5 << endl;
    cout << one << endl; 

    cout << -7 % 3 << endl;

    int x = 10;
    // 해당 표현은 지양해야 함.
    // int y = addNumbers(++x, x);
    // int z = addNumbers(x++, x);
    // cout << y << endl;
    // cout << z << endl;


    
    return 0;
}