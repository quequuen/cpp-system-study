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

### 정적 바인딩 (Static Binding)과 동적 바인딩 (Dynamic Binding)

**바인딩(Binding)**이란 프로그램 소스 코드에서 호출하는 함수와 실제 실행될 함수의 주소를 연결하는 과정. 이 연결이 언제 일어나느냐에 따라 정적과 동적으로 나뉨.

- 정적 바인딩 (Static Binding)
  컴파일 타임에 어떤 함수를 호출할 지 결정하는 방식.
  - 실행 속도가 매우 빠름. 컴파일러가 이미 호출할 함수의 주소를 알고 있기 때문.
  - 일반 함수, 오버로딩 된 함수, static 함수 등이 해당됨.
  - 포인터의 경우, 실제 가리키는 객체가 무엇인지 상관없이 포인터 변수의 타입만 보고 함수를 결정함.

    ```cpp
    Parent* p = new Child(); // 다형성
    p->print(); // 정적 바인딩이라면 Parent의 print()가 호출됨
    ```

- 동적 바인딩 (Dynamic Binding)
  동적 바인딩은 프로그램이 실행되는 시점(Runtime)에 어떤 함수를 호출할지 결정되는 방식.
  - 유연성이 뛰어남. (부모 포인터로 자식 객체를 가리킬 때, 실제 어떤 자식 객체인지 확인하고 그에 맞는 함수를 실행함.)
  - 함수가 virtual(가상 함수)로 선언 되어야 하며, 상속 관계에서 오버라이딩이 되어 있어야 함.
  - 객체 내부에 숨겨진 vtable(가상 함수 테이블) 포인터를 참조하여 실제 함수의 주소를 찾아감.

  | 구분       | 정적 바인딩 (Early Binding) | 동적 바인딩 (Late Binding)       |
  | ---------- | --------------------------- | -------------------------------- |
  | 결정 시점  | 컴파일 타임                 | 런타임 (프로그램 실행 중)        |
  | 속도       | 빠름                        | 약간 느림 (vtable 참조 오버헤드) |
  | 유연성     | 낮음                        | 높음 (다형성 구현의 핵심)        |
  | C++ 예약어 | 기본값 (일반 함수)          | virtual 키워드 사용              |
  - 동적 바인딩이 없다면, 새로운 자식 클래스를 추가할 때마다 부모 포인터를 다시 자식 타입으로 형변환(casting)해서 함수를 호출해야 함.
  - 동적 바인딩을 사용하면 부모의 인터페이스 하나만으로 수십, 수백 개의 자식 객체를 **일관된 방식**으로 제어할 수 있음. 이게 바로 다형성의 실체.

### 순수 가상 함수 (Pure Virtual Function)

부모 클래스에서 구현부({})가 없고 선언만 있는 가상 함수. 함수 선언 뒤에 = 0;을 붙여 만듦. 부모인 클래스가 정의하지 않고 부모 클래스를 상속 받는 자식 클래스가 무조건 재정의 해야 한다는 **강제성**을 부여함.

```cpp
virtual void sound() = 0;
```

### 추상 클래스 (Abstract Class)

하나 이상의 순수 가상 함수를 포함하는 클래스.

- **객체 생성 불가**: 추상 클래스는 불완전한 클래스이므로 Animal a; 와 같이 직접 이스턴스를 만들 수 없음.
- **포인터 사용 가능**: 객체는 못 만들지만, 자식 객체를 가리키는 부모 포인터 타입으로는 아주 유용하게 쓰임.
- **강제 상속**: 자식 클래스가 이 추상 클래스를 상속받았는데 순수 가상 함수를 재정의하지 않으면, 그 자식 클래스도 추상 클래스가 됨.

### 인터페이스 클래스 (Interface Class)

C++에는 interface라는 키워드가 따로 없지만, 모든 함수가 순수 가상 함수로만 이루어진 클래스를 관례적으로 인터페이스라고 부름.

- 구현은 전혀 신경 쓰지 않고, 해당 클래스를 상속 받으려면 최소 이런 함수들이 있어야 한다는 것을 알려주는 표준 규격을 정의할 때 사용.
- 멤버 변수를 가지지 않는 것이 일반적이며, 다중 상속을 통해 여러 규격을 결합할 때 최적.

```cpp
// 인터페이스 (또는 순수 추상 클래스)
class IAnimal {
public:
    virtual void makeSound() = 0; // 순수 가상 함수
    virtual void move() = 0;
    virtual ~IAnimal() {}         // 가상 소멸자는 필수
};

// 추상 클래스 (공통 기능은 구현, 핵심 기능은 자식에게)
class Mammal : public IAnimal {
public:
    void move() override { cout << "네 발로 걷습니다." << endl; }
    // makeSound()는 아직 구현 안 함 → Mammal도 추상 클래스임
};

// 구체 클래스 (Concrete Class)
class Dog : public Mammal {
public:
    void makeSound() override { cout << "멍멍!" << endl; }
};

int main() {
    // IAnimal animal; // 에러: 추상 클래스는 객체 생성 불가
    IAnimal* myPet = new Dog(); // 부모 포인터로 자식 가리킴 (다형성)
    myPet->makeSound();         // "멍멍!"
    delete myPet;
}
```

### 객체 잘림 (Object Slicing)

자식 클래스 객체를 부모 클래스 타입의 변수(값)에 대입할 때, 자식 클래스만이 가진 정보(추가 멤버 변수, 가상 함수 테이블 포인터 등)가 잘려 나가는 현상.
C++에서 객체를 값으로 전달하면 복사가 일어나게 되는데 이 때, 부모 객체 타입은 자식 객체 타입의 내용물을 다 담을 만큼 크지 않기 때문에, 부모 부분만 복사되고 버려지는 것.

```cpp
class Parent {
public:
    int p_val;
    virtual void print() { cout << "Parent" << endl; }
};

class Child : public Parent {
public:
    int c_val; // 해당 부분은 잘려 나감
    void print() override { cout << "Child" << endl; }
};

int main() {
    Child c;
    Parent p = c; // 객체 잘림 발생: p는 Parent 크기만큼만 가짐

    p.print(); // "Child"가 아닌 "Parent" 출력 (다형성 상실)
}
```

- 객체 잘림 현상을 피하려면 데이터를 값이 아닌 **주소(포인터나 참조)**로 다뤄야 함. 주소값은 크기가 일정하므로 자식 객체의 전체 모습을 그대로 유지하며 가리킬 수 있기 때문.
  - `Parent* p = &c;` (포인터 사용)
  - `Parent& p = c;` (참조자 사용)

### std::reference_wrapper

객체 잘림 현상 때문에 포인터나 참조자를 컨테이너(예: std::vector)에 담으려고 하면 문제 발생.

- vector<Parent&>: 불가능. C++ 참조자는 객체가 아니므로 컨테이너에 담을 수 없음.
- vector<Parent\*>: 가능하지만 nullptr 체크가 필요하고 메모리 관리 책임이 생겨 번거로움.
  해당 경우, **std::reference_wrapper** 사용

- 내부적으로 포인터를 가지고 있지만, 겉으로는 참조자처럼 동작을 함.
- 일반 참조자는 한 번 대상을 정하면 바꿀 수 없지만, reference_wrapper는 다른 객체를 가리키도록 바꿀 수 있음.
- 객체이므로 vector 등에 담을 수 있어 객체 잘림 없이 다형성을 유지하는 리스트를 만들기 최적임.

```cpp
#include <iostream>
#include <vector>
#include <functional> // reference_wrapper

int main() {
    Child c1, c2;
    Parent p1;

    // 객체 잘림 없이 부모/자식을 모두 담는 리스트
    std::vector<std::reference_wrapper<Parent>> v;

    v.push_back(c1);
    v.push_back(p1);
    v.push_back(c2);

    for (Parent& ref : v) {
        ref.print(); // 각자 자신의 타입에 맞는 함수 호출 (다형성 유지)
    }

    return 0;
}
```
