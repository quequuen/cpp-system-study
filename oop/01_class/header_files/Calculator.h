#pragma once
#include <iostream>


class Calculator
{
    private:
        int _value;
    
        public:
            Calculator(int init)
            : _value(init)
            {}

            Calculator &add(int value)
            {
                _value += value;
                return *this;
            }

            void print()
            {
                using namespace std;

                cout << _value << endl;
            }
};