#include <iostream>
#include <vector>

class Unit {
public:
    virtual void attack() {
        std::cout << "Unit Attack!" << std::endl;
    }
    virtual ~Unit(){} // 상속 시 소멸자는 반드시 virtual.
};

class Marine: public Unit {
public:
    void attack() override {
        std::cout << "Marine Attack!" << std::endl; 
    }
};

class Firebat: public Unit {
public:
void attack() override {
    std::cout << "Firebat Attack!" << std::endl; 
    }
};

int main()
{
    // 부모 포인터 배열에 서로 다른 자식 객체들을 담음 (다형성)
    std::vector<Unit*> army;
    army.push_back(new Marine());
    army.push_back(new Firebat());

    for (Unit* u : army) {
        u -> attack(); //u는 Unit 포인터지만, 실제 객체에 따라 다른 공격을 함.
    }

    // 메모리 해제
    for (Unit* u : army) delete u;
    
    return 0; 
}