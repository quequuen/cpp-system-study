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
    // c.protectedValue; // 에러: 외부에서도 당연히 접근 불가(main 포함)
    c.access(); // 내부 함수를 통해서만 확인 가능
}
```

### 상속 오버라이딩 (Overriding)

부모 클래스의 멤버 함수를 자식 클래스에서 재정의하는 것.

- 함수의 시그니처(이름, 매개변수, 반환형)가 완벽히 일치해야 함.
- 가상 함수(virtual)의 존재
  - virtual이 없을 시: 부모 포인터로 자식을 가리킬 때 부모 함수가 호출됨.
  - virtual이 있을 시: 부모 포인터로 자식을 가리켜도 자식의 함수(오버라이딩된 함수)가 호출됨.(다형성)
- override 키워드 (방어적 프로그래밍)
  자바나 C++에서는 자식 함수 뒤에 override라고 명시하는 것을 강력히 권장함.

  ```cpp
  class Parent {
  public:
      virtual void attack() { cout << "부모 공격" << endl; }
  };

  class Child : public Parent {
  public:
      // override를 붙이면 부모에 똑같은 함수가 있는지 검사해줌.
      void attack() override { cout << "자식 필살기" << endl; }
  };
  ```

- 네임 하이딩(Name Hiding)
  부모에게 void move()와 void move(int x) 두 개가 있을 때, 자식에서 void move()만 오버라이딩하면 매개변수가 있는 move(int x)는 **자식 객체에서 숨겨져서 호출할 수 없게 됨.**

- final 키워드로 더 이상 오버라이딩 되지 못하도록 막을 수 있음.

### 상속 받은 멤버 숨기기

- 상속 접근 지정자 사용(private 상속)
  상속을 받을 때 public 대신 private이나 protected 사용.
- using 키워드로 접근 데어 (부분 숨기기)
  public 상속을 유지하면서 특정 함수만 골라서 숨기고 싶을 때 유용. 부모의 함수를 자식의 private 영역으로 강제로 끌어내리는 방식.

  ```cpp
  class Child : public Parent {
  private:
      using Parent::display; // 부모의 public 함수를 자식의 private 영역으로 배치.
  };

  int main() {
      Child c;
      // c.display(); // 에러: 이제 자식 객체를 통해서는 접근할 수 없음.
  }
  ```

### 다중 상속 (Multiple Inheritance)

    두 개 이상의 부모 클래스로부터 기능을 물려받는 것. 콤마(,)를 이용해 상속받을 부모 클래스들을 나열.

```cpp
class Scanner {
public:
    void scan() { cout << "스캔 중..." << endl; }
};

class Printer {
public:
    void print() { cout << "출력 중..." << endl; }
};

// 다중 상속: 두 클래스의 기능을 모두 가짐
class Copier : public Scanner, public Printer {
};

int main() {
    Copier cp;
    cp.scan();
    cp.print();
}
```

- 다중 상속의 치명적인 문제: **죽음의 다이아몬드 (The Diamond of Death)**
  다중 상속은 강력해 보이지만, 설계상 매우 위험한 **모호성** 문제를 일으킬 수 있음.

  ```cpp
  class PoweredDevice { /* ... */ };
  class Scanner : public PoweredDevice { /* ... */ };
  class Printer : public PoweredDevice { /* ... */ };

  // Copier는 PoweredDevice를 두 번 상속받게 됨.
  class Copier : public Scanner, public Printer { /* ... */ };
  ```

  - 가상 상속(virtual)을 통해 최상위 부모의 인스턴스를 단 하나만 생성하여 공유하도록 강제.

    ```cpp
    class PoweredDevice { /* ... */ };

    // 가상 상속 선언
    class Scanner : virtual public PoweredDevice { /* ... */ };
    class Printer : virtual public PoweredDevice { /* ... */ };

    // 이제 Copier 내부에는 PoweredDevice가 단 하나만 존재하게 됨
    class Copier : public Scanner, public Printer { /* ... */ };
    ```

  - 복잡도 증가, 이름 충돌 등으로 인한 문제로 인해 **인터페이스(Interface, 추상 클래스)**를 상속받거나, **합성 (Composition, 클래스 내부에 다른 클래스 객체를 포함하는 것)**을 사용하는 방식이 권장됨.

### 가상 상속의 동작 원리

조상 클래스를 공유(Sharing)하는 구조로 변경. 일반 상속이 '복사'라면, 가상 상속은 **'공유'.** (위 예시 참고)

- 일반 상속의 구조 (문제가 발생하는 이유)
  일반 상속에서 Copier 객체를 만들면, 메모리 안에 PoweredDevice가 두 개 생김. → 이 상태에서 Copier.start()를 호출하면 컴파일러는 Scanner와 Printer 둘 중 어느 메소드를 사용해야 하는지 혼란에 빠짐.(모호성 발생)
- 가상 상속의 구조 (해결 방법)
  부모 클래스를 자식들 안에 직접 넣는 것이 아닌 메모리의 별도 공간에 딱 하나만 두고 분리를 함. 대신 자식 클래스 내부에는 부모 클래스가 어디에 있는지 가리키는 **가상 기본 클래스 표 포인터(Virtual Base Pointer, vbptr)**이 생성. → 모두 동일한 하나의 부모 클래스의 주소를 가리키게 됨. 결국 똑같은 메모리 주소를 공유하게 됨.
- 포인터 참조로 인한 미세한 오버헤드와 포인터 공간이 추가로 필요하므로 객체의 용량이 커질 수 있음. 또한, 가장 하위 자식이 최상위 부모를 직접 초기화해야 하는 복잡함 발생.
