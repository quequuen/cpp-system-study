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

    float my_float;

    cout << sizeof(float) << endl;
    cout << sizeof my_float << endl;    // 가능!
    // sizeof는 연산자이기 때문에 괄호 생략 가능.

    // 쉼표 연산자

    int a = 5, b = 10;
    int c = (a += 2, b += 5);
    // a += 2가 먼저 실행되고, 그 다음에 b += 5가 실행됨.
    // c에는 b += 5의 결과값이 들어감.
    int d = (++a, b--);
    int e;
    e = a, b;
    // e에는 a의 값이 들어감. 쉼표 연산자는 우선순위가 매우 낮기 때문에 대입 연산자보다 나중에 실행됨.
    // 런타임 시 warning 발생 가능.

    cout << a << " " << b << " " << c << endl;
    cout << d << endl;
    cout << e << endl;


    
    return 0;
}