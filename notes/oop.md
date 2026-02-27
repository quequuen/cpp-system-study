## 객체 지향 프로그래밍 (OOP, Object-Oriented Programming)

데이터와 로직을 객체 단위로 묶어 관리하는 패러다임. 캡슐화, 상속, 다형성, 추상화라는 4대 원칙을 가짐. 이 원칙들은 코드의 재사용성, 유지 보수성, 확장성을 높이고 복잡성을 낮추기 위해 객체들의 공통 특징을 묶고, 내부 데이터를 보호하며, 유연하게 객체를 다룰 수 있게 함.

### 클래스 (Class)와 객체 (Object)

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
