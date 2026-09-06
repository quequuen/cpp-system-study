#include <iostream>
#include <memory>

class Child;

class Parent {
public:
    std::shared_ptr<Child> son; // 부모는 자식을 강하게 소유
    ~Parent() { std::cout << "부모 소멸\n"; }
};

class Child {
public:
    // 만약 여기가 shared_ptr였다면 순환 참조 발생
    std::weak_ptr<Parent> mom; // 자식은 부모를 약하게 참조
    ~Child() { std::cout << "자식 소멸\n"; }
};

int main() {
    auto c = std::make_shared<Child>();

    {
        auto p = std::make_shared<Parent>();
        p->son = c;
        
        std::cout << "부모 카운트: " << p->son.use_count() << std::endl;
        // auto c와 그걸 참조하는 p->son: 2
        c->mom = p; 

        std::cout << "자식 카운트: " << c->mom.use_count() << std::endl;
        // c->mom은 weak_ptr이기 때문에 카운트 x, auto p가 Parent를 가리킴.: 2

        if (auto locked = c->mom.lock()) {
            std::cout << "부모 객체 존재 (lock)\n";
        }

    } // 여기서 p가 소멸. Parent의 참조 횟수가 0이 됨.

    // Parent는 소멸됐으므로 expired()가 true가 됨.
    if(c->mom.expired()) {
        std::cout << "객체가 이미 만료(소멸) 되었음.\n";
    }

    return 0;
} // 순환 참조가 없으므로 정상적으로 부모, 자식 모두 소멸됨