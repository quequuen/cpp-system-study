#pragma once
#include <iostream>

class Calculator
{
private:
    int _value;

public:
    Calculator(int init);

    Calculator &add(int value);

    void print();
};