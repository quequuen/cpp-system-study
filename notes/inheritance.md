## 상속 (Inheritance)

기존의 클래스가 가지고 있는 멤버(변수와 함수)를 새로운 클래스가 물려받아 재사용하는 것. 코드의 중복을 줄이고 계층적인 구조를 설계할 때 필수적.

- **부모 클래스 (Base/Parent Class)** : 물려주는 클래스. 공통적인 특징을 가짐.
- **자식 클래스 (Derived/Child Class)**: 물려받는 클래스. 부모의 특징에 자신만의 기능을 추가(확장).

```cpp
#include <iostream>
#include <string>

// 부모 클래스: 동물
class Animal {
public:
    void eat() { std::cout << "냠냠 먹습니다." << std::endl; }
};

// 자식 클래스: 사람 (동물의 기능을 상속받음)
class Human : public Animal {
public:
    void speak() { std::cout << "안녕하세요!" << std::endl; }
};

int main() {
    Human person;
    person.eat();   // 부모로부터 물려받은 기능 사용
    person.speak(); // 자신만의 기능 사용

    return 0;
}
```

- 공통된 기능을 부모 클래스에 한 번만 작성하면, 여러 자식 클래스에서 그대로 쓸 수 있어 **코드의 재사용성**이 좋음.
- 공통 기능에 수정이 필요할 때 부모 클래스만 고치면 모든 자식 클래스에 적용되기 때문에 **유지보수가 용이함**.
- 클래스 간의 관계를 논리적으로 조직화하여 복잡한 설계를 체계적으로 관리하는 **계층적 구조**.
