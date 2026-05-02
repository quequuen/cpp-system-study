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
    // std::string은 내부에 실제 문자열의 길이를 따로 저장하고 있기 때문에 null을 일부러 넣어주지 않아도 됨.

    char buffer2[5] = {'A', 'B', 'C', 'D', 'E'}; 
    char buffer3[5] = {'1', '2', '3', '4', '5'}; 

    std::cout << buffer << std::endl;
    std::cout << buffer2 << std::endl;
    std::cout << buffer3 << std::endl;

    buffer[2] = '\0';

    std::cout << buffer << std::endl;

    try{
        // str[22] = 'H'; // 여전히 오류
        // [] (인덱스 연산자)는 무조건 전진을 하기 때문에
        str.at(22) = 'H';
        // at은 값을 쓰기 전에 먼저 확인부터 함. 
        // 그렇기 때문에 성능은 []가 더 좋은. 하지만 안전을 위해 at()을 더 사용.
    }
    catch(std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}