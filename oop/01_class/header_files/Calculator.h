#pragma once
#include <iostream>

class Calculator
{
private:
    int _value;

public:
    static int count;

    Calculator();

    Calculator(int init);

    Calculator &add(int value);

    void print();
};