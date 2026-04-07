#include "headers/Resource.h" 

// 일반 생성자
Resource::Resource(size_t n): size(n){
    data = new int[n];
    std::cout << "자원 생성 (크기: " << size << ")\n";
}

// 소멸자
Resource::~Resource()
{
    delete[] data;
    std::cout << "자원 소멸\n";
}

// 이동 생성자: 얕은 복사 후 상대방 연결 끊음
Resource::Resource(Resource&& other) noexcept // 이동 중에 예외가 발생하면 시스템이 불안정해지므로, 예외를 절대 던지지 않는 것을 보장하며 컴파일러가 신뢰하고 이동을 수행할 수 있게 함.
// 특히 std::vector 재할당 시 중요
: data(other.data), size(other.size)
{
    other.data = nullptr; // 상대방이 소멸될 때 내 데이터를 안 지우게 함
    // 해당 부분이 없으면 other가 소멸될 때 우리가 뺏어온 메모리까지 delete 해버림 (이중 해제 에러 발생)
    other.size = 0;
    std::cout << "이동 생성 완료\n";

};

Resource& Resource::operator = (Resource&& other) noexcept
{
    if (this != &other) // 자기 자신 대입 방지
    {
        delete[] data;  // 기존 자원 해제

        data = other.data;  // 상대 자원 대입
        size = other.size;

        other.data = nullptr;   // 상대 연결 끊음
        other.size = 0;
        std::cout << "이동 대입 완료\n";
    }
    return *this;
};

void Resource::printStatus() const
{
    if (data) std::cout << "데이터 존재함\n";
    else std::cout << "데이터 없음\n";
}
