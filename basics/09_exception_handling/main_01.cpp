#include <iostream>

class Resource {
public:
    Resource() { std::cout << "자원 획득\n"; }
    ~Resource() { std::cout << "자원 자동 해제(소멸자)\n"; }
};

void func3() {
    Resource r; // 지역 객체 생성
    throw std::runtime_error("에러 발생"); // 예외 던짐
    std::cout << "이 코드는 실행되지 않음\n";
}

void func2() { func3(); }
void func1() { func2(); }

int main() {
    try {
        func1();
    } catch (const std::exception& e) {
        std::cout << "예외 처리: " << e.what() << "\n";
    }
    return 0;
}