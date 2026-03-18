## 다형성 (Polymorphism)

    사전적 의미는 하나의 모습이 여러 가지 형태를 가질 수 있는 성질. C++에서의 다형성은 부모 클래스의 포인터나 참조자로 자식 객체를 가리킬 수 있고, 이때 호출되는 함수가 실제 객체에 따라 다르게 동작하는 것.
    다형성이 없다면 각 유닛 타입별로 리스트를 따로 만들고, 각각 for문을 돌려야 함. 하지만 다형성으로 구현하면 모든 유닛의 부모인 클래스 포인터 배열 하나에 담아서, 한 번의 for문으로 공통 메서드를 호출하면 됨.

### 가상 함수 (Virtual Fuction)

다형성을 구현하기 위해서는 부모 클래스에서 함수를 선언할 때 virtual 키워드를 붙여야 함. 이를 통해 **동적 바인딩(Dynamic Binding)**이 일어남. → 실행 시점(Runtime)에 포인터가 가리키는 실제 객체가 무엇인지 확인하고, 자식이 오버라이딩한 함수를 찾아 실행.

```cpp
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
```

- 코드의 유연성 및 확장성을 증가시킴.
- 코드 객체 간의 결합도를 낮춤.

- 다형성의 두 가지 종류
  - **컴파일 타임 다형성 (Static Polymorphism)**: 함수 오버로딩, 템플릿(Template). → 컴파일 할 때 어떤 함수를 쓸 지 이미 결정됨.
  - **런타임 다형성 (Dynamic Polymorphism)**: 가상 함수 오버라이딩. → 프로그램 실행 중에 실제 객체 타입을 보고 결정됨. (개발 시 흔히 말하는 다형성)

- vtable(가상 함수 테이블)
  컴파일러는 virtual 함수가 포함된 클래스마다 vtable(Virtual Method Table)이라는 지도를 만듦. 객체는 내부적으로 이 지도를 가리키는 포인터를 가지고 있어서, 함수 호출 시 지도를 보고 어떤 경로로 갈 지를 판단. 때문에 아주 미세한 성능 비용 발생.
