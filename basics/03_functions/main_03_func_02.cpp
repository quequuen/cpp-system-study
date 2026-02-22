#include <iostream>

using namespace std;

void printSomething(int x)
{
    cout << x << endl;
}

// 보통 객체 지향 가면 이런 구조를 많이 씀
// 값을 참조 전달하는 함수에 바로 넣기 위함
// void printSomething (const int &x)
// {
//     cout << x << endl;
// }

void printSomething(int *x)
{
    *x = 10;
    cout << *x << endl;
}

int main()
{
    int x = 5;
    // 값에 의한 전달 
    printSomething(x);

    // 참조에 의한 전달
    printSomething(&x);

    
    return 0;
}