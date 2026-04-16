## 템플릿 (Templates)

코드를 찍어내는 틀. 자바의 제네릭같은 기능. 데이터 타입에 의존하지 않는 범용적인 코드를 작성하기 위한 도구 (코드 설계도). 템플릿은 그 자체로 메모리를 차지하는 '객체'가 아니라, 컴파일러에게 전달하는 **코드 생성 지시서**임. 템플릿은 이러한 특성으로 반복적인 코드 구현을 간편하게 해주지만 선언과 구현이 분리되어 있으면 링크 에러가 발생하기 쉬워 보통 헤더 파일에 모두 작성함.

### 함수 템플릿 (Function Template)

특정 데이터 타입에 종속되지 않고, 로직(알고리즘)은 같지만 다루는 자료형만 바뀔 때 사용하는 함수 생성기.

- 함수 정의 바로 위에 template <typename T>를 붙여주고 인자들의 타입을 T로 정의.

```cpp
template <typename T>
T Max(T a, T b) {
    return (a > b) ? a : b;
}
```

- 명시적 호출 (Explicit)
  개발자가 직접 어떤 타입을 사용할지 명시.

  ```cpp
  cout << Max<int>(3, 7);       // T를 int로 확정해서 호출
  cout << Max<double>(3.5, 2.1); // T를 double로 확정해서 호출
  ```

- 암시적 호출 (Implicit/ Type Deduction)
  컴파일러가 인자로 들어온 값을 보고 타입을 스스로 추론.

  ```cpp
  cout << Max(10, 20);    // 인자가 int이므로 컴파일러가 T = int로 추론
  cout << Max(1.5f, 3.2f); // 인자가 float이므로 컴파일러가 T = float로 추론
  ```

- 서로 다른 두 타입을 인자로 받고 싶다면, 콤마(,)를 사용하여 여러 개의 인자를 정의할 수 있음.

  ```cpp
  template <typename T, typename U>
  void printPairs(T a, U b) {
      cout << a << " 와 " << b << endl;
  }

  int main() {
      printPairs(202544016, "한가연"); // T는 int, U는 const char*로 결정됨
  }
  ```

- 함수 템플릿 특수화 (Template Specialization)
  다른 타입은 다 똑같은 로직인데, 특정 타입 하나만 다르게 동작해야 하는 상황에 특수화를 사용함

```cpp
// 기본 템플릿
template <typename T>
T Add(T a, T b) { return a + b; }

// char* 타입에 대해서만 특수화
template <>
const char* Add(const char* a, const char* b) {
    // 문자열 두 개를 합치는 별도의 로직
    return "Combined String";
}
```

### 클래스 템플릿 (Class Templates)

함수 템플릿의 개념을 클래스로 확장한 것. 클래스가 다루는 멤버 변수의 타입이나 메서드의 매개변수 타입을 고정하지 않고, 객체를 생성할 때 결정할 수 있게 해주는 클래스 설계도. 가장 대표적인 예시가 std::vector<T>, std::array<T>임. 둘 다 틀은 하나지만, 안에 들어가는 내용물은 제각각이라는 점에서 클래스 템플릿이라고 함.

- 템플릿은 코드 생성 지시서이기 때문에, 컴파일러가 실제 객체를 만들려고 할 때(인스턴스화), 템플릿의 전체 구현 코드를 알고 있어야 해당 타입에 맞는 클래스를 새로 찍어낼 수 있음. 그래서 템플릿 클래스는 보통 .h 파일에 선언과 구현을 모두 작성함.
- 클래스 정의 위에 template <typename T>를 붙이고, 타입이 결정되지 않은 곳에 T를 사용.

```cpp
template <typename T>
class Box {
private:
    T data; // 어떤 타입이든 담을 수 있는 변수
public:
    void setData(T value) { data = value; }
    T getData() { return data; }
};
```

- 함수 템플릿은 컴파일러가 인자를 보고 타입 추론을 해주지만, 클래스 템플릿은 기본적으로 어떤 타입인지 명시해줘야 함.

```cpp
int main() {
    // 명시적으로 타입 지정 (가장 일반적)
    Box<int> intBox;
    intBox.setData(100);

    Box<string> strBox;
    strBox.setData("Hello Template");

    // C++17 클래스 템플릿 인자 추론 (CTAD)
    // Box myBox(500); // 생성자에 500이 들어왔으므로 T를 int로 추론
}
```

- 클래스 내부가 너무 복잡해져서 함수를 밖으로 뺄 때는 모든 함수 위에 다시 템플릿 선언을 해줘야 하고 클래스 이름 뒤에 <T>를 붙여줘야 함.

```cpp
template <typename T>
void Box<T>::setData(T value) {
    data = value;
}
```

- 템플릿에는 T에 해당하는 기본 자료형뿐만 아니라 숫자(상수)도 전달 가능함. 이러한 특성으로 std::array<int, 5>와 같은 라이브러리 사용 가능.

### 템플릿 특수화 (Templates Specialization)

모든 타입에 대해 공통적인 템플릿을 사용하되, 특정 타입에 대해서만 별도의 특별한 템플릿을 사용하는 기법.

- 전체 특수화 (Full Specialization)

모든 템플릿 인자를 구체적인 타입으로 확정하는 것.

```cpp
// 일반적인 템플릿 (기본 설계도)
template <typename T>
class Formatter {
public:
    void print(T data) { cout << "일반 데이터: " << data << endl; }
};

// 전체 특수화 (char* 타입 전용 설계도)
// template 뒤의 꺽쇠를 비워두고, 클래스 이름 뒤에 타입을 명시합니다.
template <>
class Formatter<const char*> {
public:
    void print(const char* data) {
        cout << "문자열 전용 출력: [" << data << "]" << endl;
    }
};
```

- 부분 특수화 (Partial)

템플릿 인자가 여러 개일 때 일부만 확정하거나, 포인터(\*)나 참조(&) 같은 특정 형태에 대해서만 따로 정의하는 것.

```cpp
// 일반 템플릿
template <typename T, typename U>
class DualData { };

// 부분 특수화: 두 번째 인자 U를 int로 고정
template <typename T>
class DualData<T, int> { };

// 부분 특수화: 모든 포인터 타입(*)에 대해 따로 처리
template <typename T>
class DualData<T*, T*> { };
```

- 컴파일러는 가장 구체적으로 매칭되는 특수화 버전을 먼저 선택함.
- 특정 타입일 때만 컴파일이 되게 하거나 다른 기능을 제공하고 싶을 때도 유용함.
- 특수화는 완전히 새로운 클래스를 정의하는 것.**(상속이 아님)**
- 기본 템플릿 내부의 인터페이스는 똑같이 맞춰줘야 함.
- 함수 템플릿은 부분 특수화 불가능.

### 중첩 및 템플릿 템플릿 인자

템플릿 클래스의 멤버로 템플릿을 가지는 경우와 템플릿 자체를 인자로 전달받는 경우.

- 중첩 템플릿 (Member Template)
  클래스 템플릿 내부에 또 다른 템플릿 함수나 클래스를 정의하는 방식. 부모 클래스의 타입 T와는 별개로, 특전 멤버 함수만 다른 타입 U를 받아들이고 싶을 때 사용.

  ```cpp
  template <typename T>
  class Outer {
  public:
      T data;

      // 멤버 함수 자체가 템플릿 (중첩 템플릿)
      template <typename U>
      void printConvert(U value) {
          cout << "Outer T: " << data << ", Input U: " << value << endl;
      }
  };

  int main() {
      Outer<int> outer;
      outer.data = 10;
      outer.printConvert("Hello"); // T는 int, U는 const char*
      outer.printConvert(3.14);    // T는 int, U는 double
  }
  ```

- 템플릿 템플릿 인자 (Template Template Parameter)

또 다른 템플릿을 인자로 받는 템플릿. 구체적인 타입 뿐만 아니라 **데이터 구조(컨테이너)** 자체를 추상화할 때 사용. 단순한 기본 자료형보단 vector나 list 같은 틀과 같은 자료형을 통째로 넘겨받고 싶을 때 사용.

```cpp
// Container가 템플릿 틀 자체를 인자로 받음
template <typename T, template <typename> class Container>
class Wrapper {
    Container<T> contents; // 넘겨받은 틀(Container)에 타입(T)을 입힘
public:
    void add(T item) { /* contents에 추가 로직 */ }
};

int main() {
    // vector라는 '틀'과 int라는 '타입'을 전달
    Wrapper<int, std::vector> myVecWrapper;
    Wrapper<double, std::list> myListWrapper;
}
```

- 특정 데이터를 저장하는데, vector에 담을지 list에 담을지 직접 컨테이너 종류를 선택하게 하고 싶을 때 유틸리티 클래스 설계용으로 많이 씀.
- 템플릿이 중첩되면 안쪽부터 해석하는 게 보기 쉬움.
