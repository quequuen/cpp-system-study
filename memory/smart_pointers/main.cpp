#include <iostream>
#include "headers/Resource.h"
#include <vector>

// std::auto_ptr<int>과는 다른 개념. 이건 이전에 나왔지만 문제가 많아서 사라짐.

int main()
{
    Resource res1(100);

    std::cout << "res1 상태: "; res1.printStatus();

    // 이동 생성자 호출 (res1의 소유권이 res2로 이동, res1은 이제 빈 값)
    Resource res2 = std::move(res1);

    std::cout << "res1 상태: "; res1.printStatus();
    std::cout << "res2 상태: "; res2.printStatus();

    Resource res3(50);
    // 이동 대입 연산자 호출 (res3가 원래 가졌던 자원은 해제되고, res2의 자원을 뺏어옴)
    res3 = std::move(res2); 

    std::cout << "res1 상태: "; res1.printStatus();
    std::cout << "res2 상태: "; res2.printStatus();
    std::cout << "res3 상태: "; res3.printStatus();


    return 0;
}