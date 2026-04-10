#include <iostream>

class Monster {
public:
    Monster() { std::cout << "몬스터 등장!\n"; }
    ~Monster() { std::cout << "몬스터 퇴장...\n"; }
};

int main() {
    // 공유 포인터 생성 (카운트: 1)
    std::shared_ptr<Monster> p1 = std::make_shared<Monster>();

    {
        // 복사 (카운트: 2)
        std::shared_ptr<Monster> p2 = p1;
        std::cout << "현재 공유 인원: " << p1.use_count() << "\n";
    } // p2가 여기서 소멸됨 (카운트: 1)

    std::cout << "p2 소멸 후 인원: " << p1.use_count() << "\n";

    return 0;
} // p1이 소멸되면서 카운트가 0이 되어 몬스터 사라짐.