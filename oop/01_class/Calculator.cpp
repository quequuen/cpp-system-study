#include "header_files/Calculator.h"

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