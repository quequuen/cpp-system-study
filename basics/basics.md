## C++ basics(C++ 기초)

C++ 기초 문서입니다. C++ 언어의 기본 문법과 개념들을 다룹니다.

### 기본 구조

```cpp
#include <iostream>
int main(){
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```


### L-values와 R-values

- L-values: 메모리 주소를 가지는 값. 변수, 배열 요소, 참조 등이 이에 해당. 대입 연산자(=)의 왼쪽에 올 수 있음.
- R-values: 값 자체를 나타내며, 메모리 주소를 가지지 않는 값. 리터럴, 임시 객체 등이 이에 해당. 대입 연산자(=)의 오른쪽에만 올 수 있음.

```cpp
int x = 10;
int y = x + 5; // x는 L-value이지만 여기서는 임시 계산 결과를 가져오기 때문에 R-value로 사용됨.

int getValue() {
    return 42;       // 42는 R-value 반환
}

int& getRef() {
    static int x = 10;
    return x;        // x의 참조 반환 (L-value)
}
```

### 초기화(initialization)와 대입(assignment)

- 초기화: 변수를 선언하면서 처음으로 값을 할당하는 과정. 초기화를 통해 변수는 메모리에 공간을 할당받게 되고 값이 설정됨. 릴리즈 모드에서는 초기화되지 않은 변수가 0으로 설정될 수 있지만, 디버그 모드에서는 쓰레기 값이 남아 있을 수 있음. 프로그램이 예측 불가능한 동작을 할 수 있으므로 초기화는 매우 중요함.
- 대입: 이미 선언된 변수에 새로운 값을 할당하는 과정. 대입은 변수의 기존 값을 새로운 값을 덮어쓰게 됨.

### 네임 스페이스(namespaces) 기초

네임 스페이스는 C++에서 식별자(변수, 함수, 클래스 등)의 범위를 지정하는 데 사용되는 기능. 네임 스페이스를 사용하면 동일한 이름의 식별자가 충돌하는 것을 방지할 수 있음.

```cpp
#include <iostream>

int main(){
    using namespace std; // std 네임스페이스 사용
    cout << "Hello, World!" << endl; // std::cout 대신 cout 사용 가능
    return 0;
}
```

- 파이썬으로 치면 메소드를 함수화 시켜 import 하는 것과 비슷함.
  ex) from math import pi
  -> math.pi 대신 pi로 바로 사용 가능

### cout과 cin

- cout : C++에서 표준 출력 스트림을 나타내는 객체. 주로 콘솔에 텍스트를 출력하는 데 사용됨.(print, printf와 비슷)
- cin : C++에서 표준 입력 스트림을 나타내는 객체. 주로 콘솔로부터 사용자 입력을 받는 데 사용됨.(input, scanf와 비슷)

```cpp
    int a = 1; // 입력을 받기 전에는 입력 받은 값을 저장할 변수를 이미 선언해놓아야 함

    cout << "Before input, a = " << a << endl;
    cout << "Enter an integer: ";

    cin >> a; // 사용자로부터 정수형 입력을 받아 a 변수에 저장
    cout << "You entered: " << a << endl;
    return 0;
```

### 키워드(keywords)와 식별자(identifiers) 네이밍 규칙

- 키워드: C++ 언어에서 미리 정의된 예약어로, 특정 기능이나 동작을 나타냄. ex) int, return, if, else, while 등.
- 식별자: 변수, 함수, 클래스 등의 이름을 지정하는 데 사용되는 이름.
- 네이밍 규칙:
  - 식별자는 문자(알파벳 대소문자), 숫자, 밑줄(\_)로 구성될 수 있으며, 숫자로 시작될 수 없음.
  - 대소문자를 구분함.
  - 키워드와 동일한 이름을 사용할 수 없음.
  - 가독성을 위해 카멜 케이스(camelCase)나 스네이크 케이스(snake_case) 등의 명명 규칙을 따르는 것이 좋음.
  - 변수명은 보통 소문자로 구성.
  - 함수명은 보통 대문자로 시작하며 카멜 케이스를 따르는 경우가 많으며 동사 형태로 명명하는 것이 일반적.
  - 클래스명은 보통 대문자로 시작하며 카멜 케이스를 따름.
  - 설명이 필요한 경우 주석을 추가.

### 함수(functions) 기초

함수는 특정 작업을 수행하는 코드 블록으로, 재사용이 가능하고, 코드의 가독성을 높여줌. 함수는 입력 매개변수(parameter 또는 인수 argument)를 받아 작업을 수행하고, 결과를 반환(return) 할 수 있음.

```cpp
#include <iostream>

int add(int a, int b) {
    return a + b; // 두 정수를 더한 값을 반환
}

```

- 함수 선언과 정의
  - 선언(declaration): 함수의 이름, 반환 타입, 매개변수 타입을 명시.
  - 정의(definition): 함수의 실제 구현을 포함.
  - 함수 정의 내에서 다른 함수의 선언은 가능하지만, 정의는 불가능.

### 지역 범위(Local Scope)와 전역 범위(Global Scope)

- 지역 범위: 함수나 블록 내에서 선언된 변수는 해당 함수나 블록 내에서만 접근 가능.
- 전역 범위: 함수 외부에서 선언된 변수는 프로그램 전체에서 접근 가능.

```cpp
int main(){
    int localVar = 10; //지역 변수

    std::cout << "Local Variable: " << localVar << std::endl; //접근 가능

    {
        int innerVar = 20; //inner block 지역 변수
        std::cout << "Inner Varible: " << innerVar << std::endl; //접근 가능
    }

    // std::cout << "Inner Varible: " << innerVar << std::endl; //접근 불가능, 컴파일 오류 발생.
}

```

### 삼항 연산자(ternary operator)

- 조건식 ? 참일 때 값: 거짓일 때 값

```cpp
int a = 10;
int b = 20;

int maxVal = (a > b) ? a:b; // a가 b보다 크면 a, 아니면 b를 maxVal에 할당
```
