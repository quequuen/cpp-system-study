#include <iostream>

// 함수 템플릿
template<typename T> 
T getMax(T a, T b)
{
    return (a > b)? a : b;
}

// int getMax(int a, int b)
// {
//     return (a > b)? a : b;
// }

// double getMax(double a, double b)
// {
//     return (a > b)? a : b;
// }

// float getMax(float a, float b)
// {
//     return (a > b)? a : b;
// }

// char getMax(char a, char b)
// {
//     return (a > b)? a : b;
// }

int main()
{

    std::cout << getMax(2, 5) << std::endl;
    std::cout << getMax(1.2, 3.4) << std::endl;
    std::cout << getMax(1.2f, 3.4f) << std::endl;
    std::cout << getMax('g', 'y') << std::endl;

    return 0;
}