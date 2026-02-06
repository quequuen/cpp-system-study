#include <iostream>
#include "CONSTANTS.h"
#define TAX_RATE 0.1f
// c++에서는 상수를 대체하기 위해서 매크로를 쓰는거는 안 쓴다고 보면 됨.
// 대신에 const 키워드를 사용해서 상수를 정의함.
// #define은 단순히 텍스트 치환이기 때문에 디버깅이 어렵고, 타입 검사가 안 됨.
// const float tax_rate = 0.1f;
using namespace std;
using namespace CONSTANTS;

int main()
{
    double radius;

    int number = 123;
    const float tax_rate = 0.1f;
    
    // int price = number * TAX_RATE;
    int price = number * tax_rate;

    cin >> radius;

    double circumference = 2 * PI * radius;
    double area = PI * radius * radius;


    return 0;
}
