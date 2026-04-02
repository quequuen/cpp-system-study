## 클래스 (Class)와 객체 (Object)

- 클래스(Class): 객체를 만들기 위한 설계도.
- 객체(Object): 설계도를 바탕으로 메모리에 실제로 만들어진 실체.

```cpp
class Dog {
public:
    string name; // 멤버 변수
    void bark() { // 멤버 함수
        cout << name << ": 멍멍!" << endl;
    }
};

int main() {
    Dog myDog;       // 클래스(설계도)를 이용해 객체(실체) 생성
    myDog.name = "초코";
    myDog.bark();    // 초코: 멍멍!
}
```

### 접근 제한자 (Access Specifiers)

객체 지향 프로그래밍에서 클래스, 메소드, 변수 등 멤버에 대한 접근 권한을 설정하는 키워드. 데이터를 숨기는 캡슐화와 객체 간 결합도를 낮춰 코드의 보안성 및 유지 보수성을 높이며 C++에서는 세 가지 접근 제한자를 제공함.

- public: 클래스 밖에서도 누구나 접근 가능. (공개 서비스)
- private: 클래스 내부(멤버 함수)에서만 접근 가능. (내부 비밀)
- protected: 본인과 자신을 상속받은 자식 클래스까지만 접근 허용.

### 캡슐화 (Encapsulation)

데이터와 그 데이터를 처리하는 함수를 하나로 묶고, 중요한 내부 데이터는 외부로부터 숨기는 것.

- 데이터와 함수의 결합 (Bundling)
  관련된 변수(속성)와 함수(행동)를 하나의 클래스 안에 모으는 것. 관리가 용이하고 가독성이 좋아짐.
- 정보 은닉 (Information Hiding)
  객체 내부의 상세한 구현이나 데이터는 숨기고, 필요한 인터페이스(함수)만 외부로 노출.
- 주로 getter, setter가 대표적임.
- 이점
  - 데이터 무결성 보호: 외부에서 멤버 변수에 직접 접근해 말도 안되는 값을 넣는 것을 막음.
  - 유지보수성 향상: 클래스 내부 로직을 수정해도, 그 클래스를 사용하는 외부 코드(main 함수 등)는 수정할 필요가 없음. (객체 간 결합도가 낮아짐)
  - 사용자 편의성: 객체의 내부가 어떻게 돌아가는지 몰라도, 제공된 함수(public 메서드)만 사용하면 됨.

```cpp
class BankAccount {
private:
    int balance = 0; // 내부 데이터는 숨김

public:
    void deposit(int amount) { // 검증된 통로만 제공
        if (amount > 0) balance += amount;
    }

    void withdraw(int amount) {
        if (amount > 0 && balance >= amount) balance -= amount;
        else std::cout << "잔액 부족!" << std::endl;
    }

    int getBalance() const { return balance; }
};
```

### 생성자 (Constructor)

클래스의 객체를 만들 때, 그 객체의 멤버 변수들을 초기화하는 함수.

- 클래스명과 동일, 반환 타입 없음.
- 매개변수가 있는 생성자를 정의하면, 컴파일러는 기본 생성자를 자동으로 생성하지 않음. 필요하다면 직접 정의해야 함.
- 기본 생성자: 인자를 받지 않는 생성자.
- 복사 생성자: 기존 객체를 복사해서 새로운 객체를 만들 때 호출됨.
  - 복사 초기화 (Copy Initialization): = 연산자를 사용하여 객체를 생성할 때 발생. 단순 대입과는 다른 문제.
  - 반환값 최적화 (RVO: Return Value Optimiation)
    반환 시 발생하는 불필요한 복사 생성자 호출을 컴파일러가 지워주는 기술. 결과적으로 복사가 0회 호출.
  - C++에는 **소멸자가 필요하다면, 복사 생성자와 복사 대입 연산자(=)도 필요하다**는 규칙이 있음.

    ```cpp
    // NRVO: Named RVO, 명명된 반환값 최적화

    Value makeValue() {
        Value temp(100); // 이름이 있는 변수 'temp'
        return temp;     // NRVO 발생 가능
    }

    int main() {
        Value v = makeValue(); // 복사 생성자가 호출되지 않고 v가 직접 초기화됨
    }
    ```

- 멤버 초기화 리스트 (Member Initializer List): C++에서는 생성자 몸체({}) 안에서 대입하는 것보다, **초기화 리스트**를 사용하는 것이 성능상 더 유리.

  ```cpp
  Date(int m, int d, int y)
      : _month(m), _day(d), _year(y) // 여기서 바로 초기화
  {
      // 몸체는 비워두거나 추가 로직만 넣음
  }
  ```

### 위임 생성자 (Delegating Constructor)

한 생성자가 동일한 클래스의 다른 생성자를 호출하여 초기화 작업을 맡기는 것. 여러 개의 생성자를 만들다 보면 초기화 로직이 중복되는 경우가 많아 핵심 초기화 로직을 하나의 생성자에만 집중시킴.

```cpp
class Date{
private: int _year, _month, _day;

public:
    // [A] 모든 인자를 받는 '타겟 생성자' (핵심 로직 담당)
    Date(int y, int m, int d): _year(y), _month(m), _day(d)
    {
        // 복잡한 검증 로직을 여기에만 작성
        assert(m >= 1 && m <= 12);
    }

    // [B] 연도만 받는 생성자 → [A]에게 위임
    Date(int y) : Date(y, 1, 1)
    {
        // 추가 작업이 필요하면 여기서 수행
    }

    // [C] 기본 생성자 → [A]에게 위임
    Date(): Date(2026, 1, 1){ }

}
```

- 실행 순서
  - 위임된 생성자(Target)가 먼저 실행되어 멤버 변수들을 초기화함.
  - 위임된 생성자의 몸체({})가 실행됨.
  - 호출한 생성자(Delegator)의 몸체({})로 돌아와 남은 코드를 실행함.
- 다른 생성자 호출 시 멤버 변수의 개별 초기화를 동시에 할 수 없음.

### 소멸자 (Destructor)

객체의 생명 주기가 끝날 때 **가장 마지막에, 자동으로 호출되는** 특별한 함수. 객체가 사용하던 메모리나 자원을 반납하고 떠나는 뒷정리 역할.

- 이름이 클래스와 같지만 이름 앞에 물결 표시(~)를 붙임.
- 반환 타입 및 매개변수가 없음. 소멸자는 값을 리턴하지 않으며, 인자를 받을 수도 없음. 따라서 오버로딩(Overloading)이 불가능하며 클래스당 딱 하나만 존재.
- 자동 호출. 객체가 스코프를 벗어나거나, delete 키워드로 힙 메모리에서 해제될 때 시스템이 알아서 호출.
- 소멸자에서는 `throw` 사용 금지. 애초에 메모리를 날리고 끝내는 거기 때문에 `throw` 하게 되면 런타임 에러.

```cpp
class SimpleArray {
private:
    int* _data; // 동적 할당용 포인터

public:
    // 생성자에서 메모리 할당
    SimpleArray(int size) {
        _data = new int[size];
        cout << "메모리 할당됨!" << endl;
    }

    // 소멸자에서 메모리 해제
    ~SimpleArray() {
        delete[] _data;
        cout << "메모리 해제 및 소멸자 호출!" << endl;
    }
};

int main() {
    {
        SimpleArray arr(10);
    } // 여기서 arr의 스코프가 끝나며 소멸자가 자동으로 호출됨

    cout << "프로그램 종료" << endl;
    return 0;
}
```

- 실행 순서는 LIFO(Last In First Out)
- 동적 할당된 메모리 해제, 파일 닫기, 네트워크/DB 연결 종료 등의 목적으로 사용.

### this 포인터 (this Pointers)

현재 코드를 실행하고 있는 객체 자신을 가리키는 특별한 포인터. 모든 멤버 함수 안에는 보이지 않게 this 포인터가 전달됨.

- 포인터 타입: 해당 클래스의 주소를 담는 포인터.
- 자동 생성: 선언하지 않아도 멤버 함수 내에서 언제든 사용 가능.
- 정적 함수(static)에선 사용 불가: static 함수는 특정 객체의 소속이 아니라 클래스 자체의 함수이므로 this가 존재하지 않음.
- this는 상수 포인터이기 때문에 포인터 자체의 주소값을 바꿀 수는 없음. 다만 ->로 멤버의 값을 바꿀 수는 있음. (단, const 멤버 함수 안에서는 this가 가리키는 멤버의 값도 바꾸지 못함.)
- 사용법
  - 매개변수 이름과 멤버 변수 이름이 같을 때 주로 this를 사용함.
    생성자나 Setter에서 인자 이름과 멤버 변수 이름이 똑같으면, 컴퓨터는 가까운 곳에 있는 인자를 우선시함. 이때 멤버 변수를 확실히 지칭하기 위해 this->를 씀.

    ```cpp
    class Date {
    private:
        int day;
    public:
        void setDay(int day) {
            // day = day;      // 에러는 안 나지만, 인자 day에 인자 day를 대입하는 꼴
            this->day = day;   // 객체의 멤버 변수인 day에 인자 day의 값을 대입하라는 의미.
        }
    };
    ```

  - 객체 자신을 반환하여 **체이닝(Chaining)**을 할 때
    여러 함수를 마침표(.)로 이어서 한번에 실행하고 싶을 때 \*this를 리턴함.

    ```cpp
    class Date {
    public:
        Date& setYear(int y) { _year = y; return *this; }
        Date& setMonth(int m) { _month = m; return *this; }
        Date& setDay(int d) { _day = d; return *this; }
    };

    // 사용 시 (메서드 체이닝)
    today.setYear(2026).setMonth(2).setDay(27);
    ```

  - 멤버 함수 내에서 다른 함수에 나 자신을 넘겨줄 때
    someFunction(this);와 같이 현재 객체의 주소를 다른 외부 함수로 전달할 때 사용.

- this의 내부 동작 원리 (디버깅 관점)
  컴파일러는 멤버 함수를 내부적으로 다음과 같이 변형해서 처리함.
  - 작성한 코드: today.setMonth(5);
  - 컴파일러가 변경한 코드: Date::setMonth(&today, 5);

### 클래스(Class)와 const

데이터의 무결성(안정성)을 지키기 위한 아주 중요한 약속.

1. 상수 멤버 함수 (Const Member Function)
   함수 선언 뒤에 const를 붙이는 방식. 이 클래스의 멤버 변수를 절대 수정하지 않는다고 선언하는 것.
   - 멤버 변수의 값을 읽기만 하고 수정은 금지함.
   - const 객체는 오직 const 멤버 함수만 호출할 수 있음.

   ```cpp
   class Calculator
   {
   private:
    int _value;
   public:
    // const가 뒤에 붙음: _value를 수정할 수 없음.
    void print() const
    {
        // _value = 10; // 컴파일 에러(수정 불가)
        std::cout << _value << std::endl; // 읽기만 가능.
    }
   }
   ```

2. 상수 객체 (Const Object)
   클래스 인스턴스를 생성할 때 앞에 const를 붙이는 방식.
   - 생성된 객체의 상태를 변경할 수 없음.
   - 이 객체는 상수 멤버 함수(const가 뒤에 붙은 함수)만 호출 가능. 일반 함수에서 호출하려 하면 컴파일러가 막음.

   ```cpp
   int main()
   {
    const Calculator safeCalc(10);
    safeCalc.print();
   }
   ```

3. 상수 멤버 변수 (Const Member Variable)
   클래스 내부의 변수에 const를 붙이는 방식.
   - 한 번 값이 정해지면 바꿀 수 없는 고유한 속성을 만듦.
   - 반드시 **초기화 리스트(Initialization List)**를 통해서만 값을 정해줄 수 있음.

   ```cpp
   class Calculator
   {
   private:
    const int _id; // 상수 변수
   public:
    // 초기화 리스트에서 반드시 초기화해야 함.
    Calculator(int id): _id(id) {}
   }
   ```

| 위치                     | 의미                           | 핵심 효과                   |
| ------------------------ | ------------------------------ | --------------------------- |
| 함수 뒤 (void f() const) | 함수 안에서 멤버 변수 안 바꿈  | **읽기 전용** 함수임을 보장 |
| 객체 앞 (const Calc c)   | 이 객체는 안 바꿈              | 상수 멤버 함수만 호출 허용  |
| 변수 앞 (const int v)    | 이 값은 한 번 정해지면 안 바꿈 | 초기화 리스트 강제          |

- 현업에서 협업을 할 때 신뢰성과 강제성을 주기 위해 사용.
- 코드 최적화에도 도움을 주어 더 신속하고 안전한 프로그램을 만들 수 있음.

### 정적 멤버 변수 (Static Member Variable)

클래스의 특정 객체에 귀속되지 않고, 클래스 전체가 공유하는 변수.

- **공유 메모리**: 객체를 많이 만들어도 정적 멤버 변수는 메모리에 딱 하나만 존재. 모든 객체가 이 하나의 변수를 공유.
- **생명 주기**: 프로그램이 시작될 때 생성, 프로그램이 종료될 때 소멸. (객체의 생성/소멸과 무관함)
- **클래스 외부 선언**: 헤더 파일 안에서 static으로 선언만 하고, 반드시 소스 파일(.cpp)에서 초기화(정의)를 해줘야 함. (상수 정적 변수 제외)

```cpp
// Calculator.h
class Calculator {
private:
    int _value; // 각 객체마다 가짐
public:
    static int count; // 모든 객체가 공유 (선언)

    Calculator() {
        count++; // 객체가 생성될 때마다 공유 변수 증가
    }
};
```

```cpp
// Calculator.cpp
#include "Calculator.h"

// 중요: 클래스 외부에서 반드시 정의 및 초기화가 필요.
int Calculator::count = 0;
```

```cpp
// main.cpp
int main() {
    Calculator c1;
    Calculator c2;
    Calculator c3;

    // 객체 이름이 아닌 클래스 이름(Calculator::)으로 접근하는 것이 정석.
    std::cout << "현재 생성된 객체 수: " << Calculator::count << std::endl; // 출력: 3
    return 0;
}
```

### 정적 멤버 함수 (Static Member Function)

클래스 수준에서 선언되어 객체 생성 없이 클래스 이름으로 직접 호출할 수 있는 멤버 함수.

- 함수 앞에 static을 붙여 사용.
- 객체 없이 클래스명::함수명()으로 바로 호출 가능.
- 정적 함수 안에서는 일반 멤버 변수나 this 포인터 사용 불가능. 오직 정적 멤버 변수만 가능.

```cpp
static int getCount() {
    // return _value; // 에러: 일반 변수 접근 불가
    return count;    // 정적 변수 접근 가능
}
```

- **공통 상태 관리**: 모든 객체가 알아랴 하는 공통된 설정값이나 상태를 관리할 때 사용.
- **메모리 절약**: 모든 객체에 중복해서 저장할 필요가 없는 데이터를 하나만 유지하여 메모리를 아낌.
- **싱글톤 패턴(Singleton)**: 프로그램 전체에서 단 하나의 객체만 생성되도록 보장하는 디자인 패턴을 만들 때 핵심 역할.

### 친구 관계 (Friend)

다른 private 요소를 공유할 수 있는 선언.

```cpp
// Friend2 클래스의 특정함수(doSomething)에게만 Friend 클래스의 private 영역을 열어주는 구조.
#include <iostream>

using namespace std;

// 전방 선언 (foward declaration)
class Friend;

// Friend 클래스 안에서 friend void Freind2::doSomething(...)을 선언하려면, 컴파일러가 이미 Friend2 안에 doSomething이 있다는 것을 알고 있어야 함. 그래서 Friend2가 먼저 정의.
class Friend2
{
    private:
    int _value = 2;

    public:
    void doSomething(Friend& f);
};

class Friend
{
    private:
    int _value = 1;

    friend void Friend2::doSomething(Friend& f);
};

// doSomething 함수 내부에서 f._value에 접근하려면 Friend 클래스의 상세 구조(멤버 변수 등)를 알아야 함. 따라서 함수의 실제 구현은 Friend 클래스 정의가 끝난 뒤에 배치.
void Friend2::doSomething(Friend& f)
{
    cout << f._value << endl;

};

int main()
{

    Friend f;
    Friend2 f2;
    f2.doSomething(f);

    return 0;
}
```

- 캡슐화 예외: 원래 private 멤버는 외부에서 접근할 수 없지마, friend로 지정된 함수나 클래스는 예외적으로 접근 권한을 가짐.
- 단방향성: Friend가 Friend2를 친구로 등록했다고 해서, Friend2가 자동으로 Friend를 친구로 생각하지는 않음.
- 현업에서는 클래스 전체를 friend로 만들기보다, 꼭 필요한 멤버 함수만 friend로 등록하는 것을 권장. 정보 은닉(Information Hiding)이 파괴되기 때문에 두 클래스가 아주 밀접하게 연관되어 있을 때만 사용해야 함.
- 실질적으로는 전역 함수화 하는 것.

| 구분        | static 멤버 함수                                          | friend 함수                                       |
| ----------- | --------------------------------------------------------- | ------------------------------------------------- |
| 소속        | 클래스 내부                                               | 클래스 외부 (전역 범위 소속)                      |
| 접근 방식   | Calculator::getCount()와 같이 메소드 방식 (클래스의 기능) | operator+(a, b)와 같은 함수 방식 (그냥 전역 함수) |
| this 포인터 | 없음 (객체 없이 호출)                                     | 없음 (외부 함수)                                  |
| 목적        | 객체 없이 클래스 기능을 사용할 때                         | 연산자 오버로딩 등 외부와 소통할 때               |

### 익명 객체 (Anonymous Object)

변수명이 없는 임시 객체. 보통 특정 작업을 한 번만 수행하고 바로 메모리에서 사라지게 하고 싶을 때 사용.

- 이름이 없음.
- 즉시 소멸: 해당 문장이 끝나는 세미콜론(;) 지점에서 바로 소멸자(Destructor)가 호출.
- 효율성: 일회성인 객체를 구현할 때 메모리를 계속 차지할 필요가 없어서 유용함.

```cpp
Calculator calc(10);
calc.add(5);
calc.print();
// calc는 함수가 끝날 때까지 메모리에 남아있음
```

```cpp
// 객체를 만들자마자 add하고 print한 뒤 바로 사라짐
Calculator(10).add(5).print();
```

### 중첩 타입 (Nested Type)

해당 타입이 이 클래스 안에서만 의미가 있음을 명시할 때 사용. 캡슐화를 완성하는 핵심 기법.

- 이름 충돌 방지 (Namespace 역할)
- 캡슐화와 논리적 그룹화
  특정 클래스의 세부 구현을 돕는 보조 클래스를 외부에 노출하지 않고 숨길 수 있음. private 영역에 중첩 타입을 선언하면 외부로부터 보호할 수 있음.
- 접근 제어 (Access Control)
  외부 클래스의 private 멤버에 접근해야 할 때, 중첩 타입은 외부 클래스의 멤버에 접근하기가 더 수월하거나 논리적으로 긴밀한 관계를 유지하기 좋음.

```cpp
//데이터 구조의 노드(Node)
class LinkedList {
public:
    // 중첩 타입 선언
    struct Node {
        int data;
        Node* next;
    };
private:
    Node* head;
};

// 사용 시
LinkedList::Node myNode;
```

```cpp
// 상태값 정의 (Enum)
class Player {
public:
    enum class State { IDLE, RUNNING, ATTACKING }; // Player 전용 상태
};

Player::State s = Player::State::IDLE;
```

- 중첩 클래스의 내용이 너무 길어지면 원래 클래스의 가독성이 떨어지므로 이런 상황에서는 선언은 안에서 하고, 구현은 .cpp 파일 밖으로 뺌.

### 산술 연산자 오버로딩 (Arithmetic Operator Overloading)

새로 작성된 클래스 객체끼리도 +, -, \*, / 같은 기호를 마치 기본 자료형처럼 사용 가능하게 만든 기능.

- 반환타입 operator 연산자기호(매개변수)
- 연산의 우선순위나 피연산자의 개수를 바꿀 수는 없음.

```cpp
// Calculator.h

class Calculator {
private:
    int _value;
public:
    Calculator(int v = 0) : _value(v) {}

    // + 연산자 오버로딩 (멤버 함수 방식)
    Calculator operator+(const Calculator& other) const;

    void print() const { std::cout << _value << std::endl; }
};
```

```cpp
// Calculator.cpp

// c1 + c2를 하면, c1이 주체가 되어 c2를 인자로 받음.
Calculator Calculator::operator+(const Calculator& other) const {
    // 두 값을 더한 새로운 익명 객체를 생성하여 반환
    return Calculator(this->_value + other._value);
}
```

- 연산자 오버로딩은 두 가지 방식으로 구현 가능.

  | 방식               | 특징                                   | 코드 형태           |
  | ------------------ | -------------------------------------- | ------------------- |
  | 멤버 함수          | 왼쪽 피연산자가 해당 클래스일 때 사용. | c1.operator+(c2)    |
  | 전역 함수 (friend) | 왼쪽 피연산자가 클래스가 아닐 때 필수  | operator + (10, c1) |

- \+ 연산은 원래 값을 바꾸는 게 아닌 새로운 결과값을 내놓는 것. 반드시 새로운 객체를 리턴해야 함. (자기자신을 바꾸려면 \+= 사용)
- 오버로딩 불가 연산자: ., .\*, ::, ?:, sizeof 등.

### 입출력 연산자 오버로딩

작성된 클래스 객체를 std::cout이나 std::cin과 함께 자연스럽게 사용 가능하게 만드는 기능.

- friend 전역 함수가 필수인 이유 (입출력 오버로딩의 가장 중요한 포인트)
  연산 오버로딩을 멤버 함수로 만들면 왼쪽 피연산자가 자기자신(this)이어야 함.
  - cout << value; 에서 왼쪽은 std::ostream이고 오른쪽이 Value임.
  - std::ostream 클래스의 코드를 수정할 권한이 없기 때문에 클래스 외부(전역)에서 두 객체를 이어주는 함수를 만들고, 클래스 내부의 private 멤버에 접근할 수 있도록 friend 권한을 주는 것.

```cpp
// 출력 연산자 오버로딩

#include <iostream>

class Value {
private:
    int _data;
public:
    Value(int d) : _data(d) {}

    // friend 선언: 전역 함수지만 private인 _data에 접근 허용
    friend std::ostream& operator << (std::ostream &out, const Value &v) {
        out << v._data; // 출력 스트림에 데이터 삽입
        return out;      // 연쇄 출력(cout << a << b)을 위해 out 반환
    }
};
```

```cpp
// 입력 연산자 오버로딩

friend std::istream& operator >> (std::istream &in, Value &v) {
        in >> v._data; // 입력 스트림에서 데이터를 뽑아 멤버 변수에 저장
        return in;      // 연쇄 입력(cin >> a >> b)을 위해 in 반환
    }
```

- 입력 연산자는 객체의 값이 변해야 하므로 인자에 const를 붙이지 않음.
- 반환 타입은 반드시 스트임의 참조( std::ostream&, std::istream&)을 반환.
- 매개변수
  - 첫 번째 인자는 스트림 객체(out 또는 in).
  - 두 번째 인자는 클래스의 객체(출력은 const&, 입력은 &)
- 객체 자체를 다시 구현부에 넣으면 무한 루프(재귀)에 빠지므로, 반드시 기본 자료형 멤버 변수(v.data 등)을 대상으로 연산.

```cpp
// main.cpp

int main() {
    Value v(0);

    std::cout << "숫자를 입력하세요: ";
    std::cin >> v;          // operator >> 호출

    std::cout << "입력값은 " << v << "입니다." << std::endl; // operator << 호출
    return 0;
}
```

### 단항 연산자 오버로딩 (Unary Operator Overloading)

부호를 바꾸는 -, 논리 반전 !, 증감 연산자(++, --) 등을 클래스 객체에 적용하기 위해 사용.

- 기본 단항 연산자 (-, !)

  ```cpp
  class Value {
  private:
      int _value;
  public:
      Value(int v) : _value(v) {}

      // 부호 반전 연산자 (-)
      Value operator-() const {
          return Value(-_value); // 새로운 객체를 반환
      }

      // 논리 반전 연산자 (!)
      bool operator!() const {
          return _value == 0; // 0이면 true, 아니면 false
      }
  };
  ```

  - 기본 단항 연산자는 멤버 함수로 만드는 것이 일반적임.

- 증감 연산자 오버로딩 (++, --)
  - C++ 컴파일러는 전위와 후위를 구분하기 위해 **매개변수 int**라는 독특한 약속을 사용.

  - 전위 증감(++v): 참조(&)를 반환하여 연쇄 작업(++++v)이 가능하게 함.
  - 후위 증갑(v++): 컴파일러가 전위와 구분할 수 있도록 인자에 **int**를 써줌. (실제 숫자를 넣는 게. ㅏ닌 구분용)

    ```cpp
    class Value {
    private:
    int _value;
    public:
    Value(int v) : _value(v) {}

    // 전위 증감 (++v)
    Value& operator++() {
        _value++;        // 값을 먼저 증가
        return *this;    // 바뀐 자기 자신을 반환
    }

    // 후위 증감 (v++)
    Value operator++(int) { // 구분용 int 매개변수
        Value temp(*this); // 1. 현재 상태를 복사해둠
        _value++;          // 2. 실제 값을 증가시킴
        return temp;       // 3. 증가 전의 복사본을 반환
    }

    void print() { std::cout << _value << std::endl; }
    };

    int main() {
    Value v(10);

      ++v;      // v는 11이 됨
      v++;      // v는 12가 되지만, 이 문장의 결과값은 11임

      Value v2 = ++v; // v는 13, v2도 13
      Value v3 = v++; // v는 14, v3는 13

    }
    ```

- 후위 증감은 내부적으로 복사본을 만드는 과정이 추가되기 때문에 객체가 매우 크거나 복잡할 경우, 전위 증감을 쓰는 것이 성능상 더 유리함.

### 비교 연산자 오버로딩

객체와 객체를 비교하거나, 객체와 기본 자료형을 비교할 때 사용. 단순히 값을 비교하는 것을 넘어, 실제 현업엣는 데이터를 정렬(Sorting)하거나 검색(Searching)할 때 반드시 필요한 기능.

- 반환 타입은 비교 결과가 항상 참 아니면 거짓인 관계로 bool.
- 비교를 한다고 해서 객체의 내부 값이 변하면 안 되므로, 매개변수와 함수 모두 const를 붙이는 것이 철칙.

```cpp
class Value {
private:
    int _value;
public:
    Value(int v) : _value(v) {}

    // == 연산자: 두 객체의 값이 같은지 비교
    bool operator==(const Value& other) const {
        return _value == other._value;
    }

    // != 연산자: 위에서 만든 ==를 재사용하는 것이 효율적.
    bool operator!=(const Value& other) const {
        return !(*this == other);
    }

    // < 연산자: 정렬 알고리즘(std::sort)에서 필수.
    bool operator<(const Value& other) const {
        return _value < other._value;
    }
};
```

- C++ 표준 라이브러리(STL)의 많은 기능이 < 연산자에 의존.
  - std::sort: 데이터를 오름차순으로 정렬할 때 내부적으로 < 연산자를 사용.
  - std::mop, std::set: 데이터를 저장할 때 크기 순서대로 정렬해서 보관하는데, 이때 < 연산자가 없으면 컴파일 에러 발생.
- 10 == v와 같은 형태도 구현하려면 friend 사용.
- 우주선 연산자 (<=>)
  최근 C++에서는 <=>(Three-way comparison) 가능.

  ```cpp
  #include <compare>

  class Value {
      int _value;
  public:

      auto operator<=>(const Value&) const = default;
  };
  ```

### 첨자 연산자 오버로딩 (Subscript Operator Overloading)

클래스 객체를 마치 배열처럼 다룰 수 있게 해주는 기능. 주로 리스트, 행렬, 문자열 등 '데이터 묶음'을 관리하는 클래스에서 필수적으로 사용됨. 핵심은 L-value(수정 가능)와 R-value(읽기 전용) 두 가지 버전을 세트로 만드는 것.

- [] 연산자는 반드시 멤버 함수로만 오버로딩 가능.(전역 함수/friend 불가)
- 보통 인덱스 번호인 int를 받지만, 필요에 따라 std::string 등을 받아 맵(Map)처럼 사용 가능.
- 내부 요소의 참조(&)를 반환해야 값을 직접 수정 가능.
- **직관적인 데이터 접근**과 **안전한 범위 검사**라는 두 마리 토끼를 잡기 위해 사용.

```cpp
#include <iostream>
#include <cassert> // 단언문(assert) 사용을 위해

class IntList {
private:
    int _list[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

public:
    // 일반 버전: 수정이 가능함
    int& operator[](const int index) {
        assert(index >= 0 && index < 10); // 인덱스 범위 체크 (안전장치)
        return _list[index];
    }

    // Const 버전: 읽기 전용 (const 객체용)
    const int& operator[](const int index) const {
        assert(index >= 0 && index < 10);
        return _list[index];
    }
};

int main() {
    IntList my_list;

    my_list[3] = 100; // 일반 버전 호출 (수정 가능)
    std::cout << my_list[3] << std::endl; // 100 출력

    const IntList const_list;
    // const_list[3] = 100; // 에러: const 버전은 수정 불가
    std::cout << const_list[3] << std::endl; // 읽기는 가능

    return 0;
}
```

- 범위 검사 (Bound Checking): 배열의 인덱스를 벗어나는 접근을 막기 위해 assert나 if문을 사용해 범위를 체크해주는 것이 필수.
- 포인터와의 차이: 일반 배열 포인터는 범위를 체크할 방법이 없지만, 오버로딩된 []는 함수이기 때문에 내부에서 에러 처리 가능.
- 연쇄 접근: 2차원 matrix[1][2]를 구현하고 싶다면, matrix[1]이 다시 [] 연산자가 구현된 객체를 반환하게 설계하면 됨.

### 괄호 연산자 오버로딩 (Function Object, Functor)

클래스 객체를 일반 함수처럼 호출할 수 있는 기능. 객체 내부의 멤버 변수를 통해 호출 횟수, 누적 값 등 자신만의 상태를 유지할 수 있음.

```cpp
#include <iostream>

class Accumulator {
private:
    int _total = 0; // 상태 저장

public:
    // 괄호 연산자 오버로딩
    int operator()(int value) {
        _total += value;
        return _total;
    }

    int getTotal() const { return _total; }
};

int main() {
    Accumulator acc; // 객체 생성

    // 객체를 함수처럼 호출
    std::cout << acc(10) << std::endl; // 10 출력
    std::cout << acc(20) << std::endl; // 30 출력
    std::cout << acc(5) << std::endl;  // 35 출력

    return 0;
}
```

- 인자의 개수나 타입에 제한이 없으며, 여러 개를 오버로딩 하는 것도 가능.
- 상태가 필요한 계산 뿐만 아니라 STL 알고리즘의 보조 도구, 다차원 인덱싱 등에 사용.
- 최신 C++에서 자주 쓰이는 람다 식은 컴파일러가 내부적으로 이런 함수 객체(Functor)를 자동으로 생성해 주는 것.

### 형 변환 연산자 오버로딩 (Type Conversion Operator Overloading)

클래스 객체를 기본 자료형이나 다른 클래스 타입으로 자동 혹은 명시적으로 변환할 수 있게 해주는 기능.

- 다른 연산자들과 달리 반환 타입을 적지 않은. 함수 이름 자체가 반환 타입을 의미하기 때문.
- 의도치 않게 타입이 변해버리는 "암시적 변환"을 방지하기 위해 explicit 키워드 권장.

```cpp
class Value {
private:
    int _value;
public:
    Value(int v) : _value(v) {}

    // explicit: 컴파일러가 멋대로 변환하지 못하게 막는 키워드
    explicit operator int() const {
        return _value;
    }
};

int main() {
    Value v(42);

    // int n = v;     // 암시적 변환 금지
    int n = (int)v;   // 직접 형 변환을 써줘야만 가능
    int m = static_cast<int>(v); // 권장되는 방식
}
```

- 현업에서는 반드시 const를 사용. (형 변환을 한다고 원본 객체의 값이 바꾸면 안됨)
- explicit bool 사용.
- 사용자가 예측하기 어려운 형 변환은 지양.

### explicit(암시적 형 변환 금지)과 delete(특정 기능 사용 금지)

- explicit
  - explicit은 주로 생성자나 형 변환 연산자 앞에 붙여서, 컴파일러가 멋대로 타입을 바꾸는 '암시적 변환'을 막을 때 사용.
  - 컴파일러는 인자가 하나인 생성자가 있으면, 그 인자 타입의 데이터를 객체로 자동으로 바꿔주려 하는데 당장은 편리하지만 가끔 예기치 못한 버그 발생 가능성 존재.

  ```cpp
  class MyInt {
  public:
      explicit MyInt(int n) { /* ... */ }
  };

  void doSomething(MyInt obj) { /* ... */ }

  int main() {
      // explicit이 없을 때
      // doSomething(10); // 컴파일러가 10을 MyInt(10)으로 몰래 바꿈 (의도치 않은 동작)

      // explicit이 있을 때:
      // doSomething(10); // 에러: 명시적으로 MyInt(10)을 넘겨야 함
      doSomething(MyInt(10));
  }
  ```

- delete
  - 컴파일러가 자동으로 만들어주는 함수를 금지하거나, 특정 타입의 인자를 받는 함수를 거부하라고 할 때 사용.
  - 복사 방지: 객체가 복사되면 안되는 경우 (ex: 파일 관리자, 네트워크 연결 객체 등) 복사 생성자와 복사 대입 연산자를 delete.

    ```cpp
    class UniqueManager {
    public:
        UniqueManager() {}

        // 복사 생성자와 복사 대입 연산자 금지
        UniqueManager(const UniqueManager& src) = delete;
        UniqueManager& operator=(const UniqueManager& src) = delete;
    };

    int main() {
        UniqueManager a;
        // UniqueManager b = a; // 에러: 복사 기능을 삭제했기 때문
    }
    ```

  - 특정 타입 호출 방지: 특정 타입의 인자가 들어오는 것을 아예 막을 수도 있음.

    ```cpp
    void printInt(int n) { /* ... */ }

    // double로 호출하는 것은 금지하고 싶을 때
    void printInt(double d) = delete;

    int main() {
        printInt(10);   // OK
        // printInt(3.14); // 에러: double 버전은 삭제됨
    }
    ```

### 얕은 복사 (Shallow Copy)

객체를 복사할 때 멤버 변수의 값만 그대로 복사하는 방식.

- 포인터 변수가 있다면, 가리키고 있는 실제 데이터의 주소값만 복사.
- 두 객체가 동일한 메모리 주소를 가리킴. → 추후, 한 객체에서 데이터를 수정하면 다른 객체의 데이터도 수정. 또한, 객체가 소멸할 때 같은 메모리를 두 번 해제하려다 Double Free 에러 발생 가능성 존재.

```cpp
// 컴파일러가 자동으로 만드는 복사 생성자의 모습
MyString(const MyString& src) {
    _data = src._data;   // 주소값만 복사
    _length = src._length;
}
```

- 얕은 복사는 빠르지만 메모리 오염 및 에러 유발 가능성이 있어 포인터 멤버를 절대 금지하고 있음.

### 깊은 복사 (Deep Copy)

객체를 복사할 때 새로운 메모리 공간을 할당, 안의 실제 내용물까지 복사하는 방식.

- 포인터 변수는 자신만의 독립적인 메모리 주소를 가짐.
- 두 객체는 완전히 독립적인 관계를 이루며, 추후 한쪽을 수정하거나 삭제해도 다른 쪽에 영향을 주지 않음.
- 개발자가 직접 **복사 생성자**와 **대입 연산자**를 오버로딩하여 구현해야 함.

```cpp
// 직접 정의한 깊은 복사 생성자
MyString(const MyString& src) {
    _length = src._length;
    _data = new char[_length]; // 새로운 메모리 공간 확보

    for (int i = 0; i < _length; ++i) {
        _data[i] = src._data[i]; // 내용물 하나하나 복사
    }
}
```

### initializer_list (#include <initializer_list>)

컴파일러가 {} 안에 든 내용을 보고 임시 메모리에 내용을 담음. → 이 메모리를 생성자에게 전달. → 생성자 안에서 for 문을 돌리며 메모리에 있는 데이터들을 클래스의 실질적인 메모리에 옮김.

### 컨테이너 클래스 (Container Class)

내부적으로 다른 객체들을 저장하고 관리하는 것을 목적으로 하는 클래스.

- 저장 (Insert/Add): 데이터를 바구니에 넣음.
- 삭제 (Remove/Delete): 데이터를 바구니에서 뺌.
- 조회 (Search/Find): 특정 데이터를 찾음.
- 정렬 (Sort): 데이터를 순서대로 나열함.

- 형태
  - 값에 의한 컨테이너 (Container of Values)
    객체의 복사본을 직접 저장. **구성 관계(Composition)** 활용.
    - 컨테이너가 소멸할 때 데이터들도 함께 사라짐. 안전하고 단순.
    - 멤버 변수.
  - 참조에 의한 컨테이너 (Container of Pointers)
    객체의 주소(포인터)를 저장. **집합 관계(Aggregation)**를 활용.
    - 외부에서 생성된 객체를 가리키기만 함. 컨테이너가 사라져도 원본 데이터는 남음.
    - 포인터 형태로 관리.

- 주의점
  - **동적 할당과 메모리 관리**: 대부분의 컨테이너는 실행 중에 크기가 변하므로 new와 delete[]를 적절히 사용해야 함.
  - **깊은 복사(Rule of Three)**: 컨테이너를 복사할 때 데이터가 꼬이지 않도록 복사 생성자와 대입 연산자를 반드시 구현해야 함.
  - **연산자 오버로딩**
    - []: 배열처럼 접근하기 위해 필요.
    - <<: 컨테이너 내용을 한 번에 출력하기 위해 필요.
  - **템플릿(Template)**: 함수나 클래스를 개별적으로 다시 작성하지 않아도, 여러 자료 형으로 사용할 수 있도록 만들어 놓은 틀.

- C++ 표준 컨테이너 (STL)
  Standard Template Library.
  - std::vector: 크기가 변하는 동적 배열.
  - std::list: 노드들이 연결된 연결 리스트.
  - std::map: 키(Key)와 값(Value)의 쌍으로 저장하는 사전 형태.

### 싱글톤 패턴 (Singleton)

어떤 클래스의 인스턴스가 딱 하나만 존재하도록 보장하는 디자인 패턴. → 해당 객체는 여기저기서 여러 개 만들 필요가 없고, 오직 하나만 만들어서 모두가 공유하려 할 때 사용. **관리자 (Manager)**와 같은 역할. 프로그램 내에서 중심을 잡고 자원을 관리하는 객체를 만들 때 아주 유용.

- C++에서는 static, private, delete 사용.
- 생성자를 private으로 숨기고 static으로 정적 상태를 유지하며 외부에서 이 객체를 호출할 수 있도록 get~() 같은 함수를 만듦.

```cpp
class Manager {
private:
    // 외부에서 생성 못하게 막음
    Manager() { std::cout << "매니저 생성됨!" << std::endl; }

public:
    // 복사와 대입 금지 (딱 하나만 존재해야 함.)
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    // 단 하나의 인스턴스를 반환하는 static 함수
    static Manager& getInstance() {
        // 지역 정적 변수는 함수가 처음 호출될 때 딱 한 번만 초기화됨
        static Manager instance;
        return instance;
    }

    void doSomething() { std::cout << "열심히 일하는 중..." << std::endl; }
};

int main() {
    // Manager m1; // 에러: 생성자가 private임

    // 어디서든 getInstance()를 통해 동일한 객체에 접근
    Manager& m1 = Manager::getInstance();
    Manager& m2 = Manager::getInstance();

    m1.doSomething();

    // m1과 m2는 주소값이 같음. (static 키워드로 인한 같은 객체)
    std::cout << &m1 << " == " << &m2 << std::endl;
}
```

- 위에서 사용된 delete는 메모리 해제 연산자 delete와 다름. 기능 삭제를 의미하는 키워드 delete임.

  ```cpp
  // 메모리 해제 연산자 delete
  delete prt;

  // 기능 삭제 키워드 delete
  void func() = felete;
  ```

- 주요 목적
  - **자원 공유**: 데이터베이스 연결 객체, 설정 파일 관리자, 로그 기록기(Logger)처럼 시스템 전체에서 하나만 있어도 충분하고, 오히려 여러 개면 데이터가 꼬일 수 있는 경우에 사용함.
  - **메모리 절약**: 인스턴스를 매번 new로 생성하지 않고 이미 만들어진 것을 재사용하므로 메모리 낭비를 줄임.
  - 전역 접근: 어디서든 이 객체레 접근할 수 있는 통로 제공.
