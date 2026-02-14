#include <iostream>
#include <cstring>

int main() {
    char str[] = "Hi";
    char dest[50];
    
    std::cout << "배열 크기: " << sizeof(str) << std::endl; // 3 출력
    std::cout << "글자 수: " << strlen(str) << std::endl;  // 2 출력
    
    // 종단 문자 확인
    if (str[2] == '\0') {
        std::cout << "2번 인덱스에 Null 문자가 있습니다." << std::endl;
    }

    if(strcmp(str, dest) == 0)
    {
       
    }

    std::string cppStr = "Hello";
    const char* cStr = cppStr.c_str(); // C 스타일 주소값 반환

    std::cout << &cppStr << std::endl;  // 집의 주소
    std::cout << &cStr << std::endl;    // 집주소가 적힌 메모지의 주소
    
    return 0;
}