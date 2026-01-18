#include <iostream>

int main(){
    int a = 123; // int(정수형) 타입의 a라는 이름의 변수를 선언(declaration)하고, 123이라는 숫자 값으로 초기화(initialization)
    a = 456; // a라는 메모리 공간 안에 456이라는 숫자 값을 대입(assignment)

    std::cout << a << std::endl;
    std::cout << &a << std::endl;   // &(주소 연산자) 사용으로 123이 저장된 메모리 주소 출력

    int b = 1;
    b = b + 3;
    
    std::cout << b << std::endl; // 4 출력

    int c = a;
    std::cout << c << std::endl; // 456 출력

    std::cout << b + c << std::endl; //460 출력
    std::cout << b << std::endl; // 4 출력

    int d;

    std::cout << d << std::endl; //쓰레기값 출력. 현재는 1이 출력됨.

    return 0;
}