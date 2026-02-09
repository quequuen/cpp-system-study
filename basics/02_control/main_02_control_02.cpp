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

    bool flag1 = true;
    bool flag2 = false;

    const int result = flag1 && flag2 ? 100 : 200;
    // flag1 && flag2가 true이면 100, false이면 200이 result

    cout << result << endl;

    // 부동 소수점과 관계 연산자 오차 범위 잡기

    double my_d1 = 0.1 + 0.1 + 0.1;
    double my_d2 = 0.3;

    const double epsilon = 0.00001;

    if (std::abs(my_d1 - my_d2) < epsilon)
    {
        cout << "my_d1 and my_d2 are considered equal." << endl;
    }
    else
    {
        cout << "my_d1 and my_d2 are NOT equal." << endl;
    }
    
    return 0;
}