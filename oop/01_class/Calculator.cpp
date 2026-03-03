#include "header_files/Calculator.h"

Calculator::Calculator()
{
    count++;
}

Calculator::Calculator(int init)
: _value(init)
{}

Calculator& Calculator::add(int value)
{
    _value += value;
    return *this;
}

void Calculator::print()
{
    using namespace std;

    cout << _value << endl;
}

int Calculator::getCount()
{
    // return _value; // 일반 변수 접근 불가
    return count;
}

// 클래스 외부에서 반드시 정의 및 초기화 필요.
int Calculator::count = 0;