#include <string>
#include <iostream>

int main()
{
    std::string str = "Hello";

    // string → char[]
    // .c_str()
    // '읽기 전용' 포인터 획득
    const char* c_ptr = str.c_str();
    std::cout << "str.c_str(): " << c_ptr << "(" << &c_ptr << ")" << std::endl;  

    // char[]
    // 실제 char 배열로 복사

    char buffer[10];
    str.copy(buffer, 5); // 5글자 복사
    buffer[5] = '\0';    // C 스타일은 끝에 NULL 문자를 직접 넣어줘야 함.
    // → char 배열은 문자열의 끝을 알리기 위해 반드시 마지막에 null이 있어야 하기 때문.
    // 없으면 출력할 때 메모리의 엉뚱한 곳까지 읽어버림

    char buffer2[5] = {'A', 'B', 'C', 'D', 'E'}; 
    char buffer3[5] = {'1', '2', '3', '4', '5'}; 

    std::cout << buffer << std::endl;
    std::cout << buffer2 << std::endl;
    std::cout << buffer3 << std::endl;

    buffer[2] = '\0';

    std::cout << buffer << std::endl;

    return 0;
}