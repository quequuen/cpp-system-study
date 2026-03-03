#include <iostream>
#include "header_files/Calculator.h"

int main()
{
    
    Calculator calc(2);
    
    calc.add(20);
    calc.print();

    std::cout << "현재 생성된 객체 수: " << Calculator::count << std::endl;

    Calculator c1;
    Calculator c2;
    Calculator c3;

    std::cout << "현재 생성된 객체 수: " << Calculator::count << std::endl;

    
    return 0;
}