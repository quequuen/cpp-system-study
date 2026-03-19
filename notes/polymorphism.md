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

### 공변 반환값 (Covariant Return Type)

    상속 관계에서 오버라이딩을 할 때, 부모 클래스의 함수가 반환하는 타입의 '자식 타입'으로 반환형을 바꿀 수 있게 허용하는 예외 규칙.
    보통 오버라이딩의 경우, 함수의 이름, 매개변수, 반환형이 모두 일치해야 하지만, 반환형이 포인터나 참조자일 경우, 더 구체적인 자식 타입을 반환하는 것이 논리적으로 안전하기 때문에 C++에서 특별히 허용해 주는 것.

- 부모 클래스로부터 자식 클래스에서 override 하는 메서드가 있을 시, 반환형이 부모 클래스가 되어 버리면 필수적으로 형변환을 해야 함.

  ```cpp
  class Parent {
  public:
      virtual Parent* clone() { return new Parent(); }
  };

  class Child : public Parent {
  public:
      // 반환형을 Parent*로 유지해야 함.
      Parent* clone() override { return new Child(); }
  };

  int main() {
      Child* c1 = new Child();
      // clone()이 Parent*를 반환하므로 Child*에 담으려면 캐스팅이 필요함.
      Child* c2 = static_cast<Child*>(c1->clone());
  }
  ```

- 공변 반환값을 사용한다면 이러한 형 변환 없이 메서드 사용 가능.

  ```cpp
  class Child : public Parent {
  public:
      // 부모의 반환형(Parent*)의 자식 타입(Child*)으로 반환형 변경 가능. (공변 반환값 사용)
      Child* clone() override { return new Child(); }
  };

  int main() {
      Child* c1 = new Child();
      // 형변환 없이 바로 Child* 타입으로 받을 수 있음
      Child* c2 = c1->clone();
  }
  ```

- 반환값이 포인터나 참조자여야 사용 가능.
- 상속 관계이면서 부모 함수가 virtual이어야 함.
- 주로 **프로토타입 패턴 (Prototype Pattern)**처럼 자기 자신과 똑같은 객체를 생성해서 반환해야 하는 경우에 필수적으로 사용됨. 사용자가 자식 객체임을 알고 쓰는 상황에서 불필요한 다운 캐스팅 코드를 줄여주어 가독성과 안정성을 높여줌.

### 가상 소멸자 (Virtual Destructor)

상속 관계에 있는 객체를 다룰 때 메모리 누수(Memory Leak)를 방지하기 위한 필수 장치. 다형성을 이용해 부모 클래스의 포인터로 자식 객체를 가리킬 때, 소멸자에 virtual이 자식 클래스의 메모리가 소멸되지 붙어있지 않으면 문제 발생.

```cpp
class Parent {
public:
    Parent() { cout << "Parent 생성" << endl; }
    ~Parent() { cout << "Parent 소멸" << endl; } // 일반 소멸자
};

class Child : public Parent {
private:
    int* _data;
public:
    Child() {
        _data = new int[100]; // 자식만 가진 동적 할당 자원
        cout << "Child 생성" << endl;
    }
    ~Child() {
        delete[] _data;
        cout << "Child 소멸 (자원 해제)" << endl;
    }
};

int main() {
    Parent* p = new Child(); // 다형성 활용
    delete p; // 문제 발생: 자식의 동적 자원 해제 안됨. → 메모리 누수 발생.
    return 0;
}
```

위 상항에서 부모 클래스의 소멸자 앞에 virtual 키워드를 붙여주면 컴파일러는 부모 클래스를 해제 할 때, 실제 객체의 소멸자 (자식 클래스 소멸자)를 찾아감.

```cpp
class Parent {
public:
    virtual ~Parent() { cout << "Parent 소멸" << endl; } // 가상 소멸자 선언
};
```

- virtual 키워드를 사용했을 때 순서: Child 소멸자 → Parent 소멸자 순으로 호출.
- 상속을 염두에 둔 클래스라면 무조건 가상 소멸자를 써야 하며 가상 함수가 하나라도 있는 클래스는 소멸자도 virtual로 만드는 것이 안전함.
