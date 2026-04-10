#include <iostream>
#include <memory>

class Player {
    public: 
    Player() { std::cout << "플레이어 생성\n"; }
    ~Player() { std::cout << "플레이어 소멸\n"; }
    void shout() { std::cout << "shoutinggggggg\n"; }
};

int main()
{
    std::unique_ptr<Player> ptr1 = std::make_unique<Player>();

    ptr1 -> shout();

    //std::unique_ptr<Player> ptr2 = ptr1; //unique_ptr은 복사 안 됨.

    std::unique_ptr<Player> ptr3 = std::move(ptr1);
    // 여기서 ptr1은 nullptr이 되고, ptr3가 소유권을 가짐.

    if (!ptr1) std::cout << "ptr1은 nullptr입니다.\n";

    return 0;
}