#include <iostream>
#include <string>

using namespace std;

double divide(double a, double b)
{
    if (b == 0)
    {
        throw std::string("0으로 나눌 수 없습니다.");
    }
    
    return a / b;
}

int main()
{
    // try, catch, throw

    double x = 10;
    double y = 0;

    std::cin >> y;

    try
    {
        double result = divide(x, y);
        std::cout << "결과: " << result << std::endl;
    }
    catch (const std::string& errorMsg)
    {
        std::cerr << "에러 발생: " << errorMsg << std::endl;
    }

    std::cout << "프로그램이 죽지 않고 계속 실행됩니다..." << std::endl;
   
    


    return 0;
}