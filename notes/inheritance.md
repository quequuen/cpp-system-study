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

### 상속과 접근 제한자

- **기본 원칙**: 부모의 'private'은 어떤 방식으로 상속받아도 자식이 접근할 수 없음.
- **상속 접근 지정자**:
  - 'public' 상속: 부모의 접근 권한을 유지하며 상속. (public은 public으로, protected는 protected로 가져옴.)
  - 'protected' 상속: 부모의 public 멤버도 자식에게 오면 protected가 됨. (즉, 외부에서는 못 쓰게 막고, 나를 상속받을 자식, 손자들에게만 물려주겠다는 의미.)
  - 'private' 상속: 부모의 모든 유산을 자식 선에서 **개인 소유**로 돌림. (자식 클래스 내부에서만 부모 기능을 쓰고, 그 아래 후손들에게는 아무것도 물려주지 않겠다는 강한 의지 표현.)

```cpp
class Parent {
protected:
    int protectedValue = 10;
};

// private 상속: 부모의 모든 유산을 자식의 private 영역으로 가져옴
class Child : private Parent {
public:
    void access() {
        // 자식 내부에서는 부모의 protected 멤버에 접근 가능
        cout << protectedValue << endl;
    }
};

class GrandChild : public Child {
public:
    void access() {
        // 에러: 부모(Child)가 private 상속을 받았기 때문에
        // 손자에게는 이 데이터가 보이지 않음.
        // cout << protectedValue << endl;
    }
};

int main() {
    Child c;
    // c.protectedValue; // 에러: 외부에서도 당연히 접근 불가
    c.access(); // 내부 함수를 통해서만 확인 가능
}
```
