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

### 전처리기(preprocessor)

전처리기는 컴파일러가 소스 코드를 본격적으로 번역하기 직전에 실행되는 단계. 코드의 내용을 미리 조작하는 '사전 편집기'이기 때문에 멀티플랫폼 소프트웨어 개발에서의 OS 환경, 그래픽카드 사양 결정 등에서 사용.

1. #define (매크로 정의)
   특정 단어를 단어 코드나 값으로 치환하라고 명령.

- 상수 정의 또는 매크로 함수 생성.
- 예시: #define PI 3.14159 정의, 이후 코드의 모든 PI는 컴파일러에 의해 3.14159로 수정.
- 주의:
  - C++에서는 단순 상수 정의 시 const나 constexpr을 더 권장하지만, 전처리기는 여전히 강력한 도구
  - 해당 파일 내에서만 적용.

2. #ifdef & #ifndef (조건부 컴파일)
   특정 매크로가 정의되어 있는지 여부에 따라 코드를 포함하거나 제외합니다.

- #ifdef (if defined): "만약 이 매크로가 정의되어 있다면 아래 코드를 실행해라."
- #ifndef (if not defined): "만약 이 매크로가 정의되어 있지 않다면 아래 코드를 실행해라."
- 헤더 가드(Header Guard)에 활용.
- #else로 축약 가능.
- 주의: #endif를 통해 종료 지점을 표시해 주어야 한다.

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
  → math.pi 대신 pi로 바로 사용 가능
- using namespace name;은 아무데서나 삽입 가능하지만 링킹 과정에서 다른 파일에도 영향이 갈 수 있으니 되도록이면 중괄호 내에 구현.
- 네임 스페이스 안에 네임 스페이스 구현 가능함.
- 네임 스페이스 이름은 다른 파일이든 같은 파일이든 같아도 상관 없지만 같은 네임 스페이스 안에서의 중복 정의는 컴파일 에러를 일으킴 → 컴파일/링크 시 하나의 네임스페이스로 취급되기 때문.

```cpp
// file1.cpp
namespace math
{
  int add(int a, int b)
  {
      return a + b;
  }
}

// file2.cpp
namespace math
{
  int sub(int a, int b)
  {
      return a - b;
  }
}
```

- 컴파일/링크 시 math 네임스페이스가 합쳐져서 컴파일/링크 시 하나의 네임스페이스로 취급됨. (하지만 동일한 시그니처의 동일한 이름을 가지는 심볼이 생길 시 오류.)

- 시그니처를 달리 한 오버로딩은 가능.

```cpp
namespace math
{
  int add(int a, int b);
  double add(double a, double b);
}
```

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

using namespace std;

int add(int a, int b) { // 함수 정의
    return a + b; // 두 정수를 더한 값을 반환
}

int main() {
    cout << "2 + 3 = " << add(2, 3) << endl;

    return 0;
}

```

```cpp
#include <iostream>

using namespace std;

int add (int a, int b); // 함수 선언

int main() {
    cout << "2 + 3 = " << add(2, 3) << endl;

    return 0;
}

int add (int a, int b) {
    return a + b; // 함수 정의
}
```

- 함수 선언과 정의
  - 선언(declaration): 함수의 이름, 반환 타입, 매개변수 타입을 명시.
  - 정의(definition): 함수의 실제 구현을 포함.
  - 함수 정의 내에서 다른 함수의 선언은 가능하지만, 정의는 불가능.
  - 함수 선언은 보통 함수가 사용되기 전에 이루어져야 함.

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

### 헤더 파일(Header Files) 기초

헤더 파일은 함수 선언, 클래스 정의, 상수 정의 등을 포함하는 파일로, 코드의 재사용성과 모듈화를 높여줌. 일반적으로 '.h' 확장자를 가짐.

```cpp
#include <iostream>

using namespace std;

int addNumbers(int a, int b)
{
    return a + b;
}
```

```cpp
// utils.h
#pragma once


int addNumbers(int a, int b);
```

```cpp
// main.cpp
#include "utils.h"

using namespace std;

int main()
{
    int sum = addNumbers(5, 10);
    cout << "Sum: " << sum << endl;
}
```

- '#pragma once'는 헤더 파일이 여러 번 포함되는 것을 방지하는 전처리기 지시문.
- 헤더 파일에는 함수 정의보다는 함수 선언을 포함하는 것이 일반적임.
- 헤더 파일을 포함할 때는 큰 따옴표("")를 사용하여 로컬 파일을 포함함.

### 링킹 에러(Linking Error)

- 컴파일에 성공한 여러 파일 조각(.o)을 하나로 합치는 과정
- 컴파일은 성공했는데 프로그램 빌드 과정(전처리 → 컴파일 → 링킹)에서 여러 파일을 연결할 때 발생하는 에러.

```cpp
// 기존 utils.h (헤더 가드 없음)
struct Point {
    int x;
    int y;
};

int add(int a, int b);
```

```cpp
// 기존 main.cpp
#include "utils.h"
#include "utils.h"  // 실수로 두 번

int main() {
    return 0;
}
```

```cpp
// 전처리 후 main.cpp
struct Point {  // 첫 번째 include
    int x;
    int y;
};
int add(int a, int b);

struct Point {  // 두 번째 include (중복)
    int x;
    int y;
};
int add(int a, int b);

int main() {
    return 0;
}
```

**컴파일 에러:**

```
error: redefinition of 'struct Point'
```

- 해당 상황 말고도 중복 정의나 잘못된 빌드 등으로도 발생할 수 있음.

### 헤더 가드(Header Gaurd)

- 컴파일 에러(중복 선언∙정의 등)을 방지하며 헤더 파일 상단에 전처리기 지시문을 추가.

- 방법 1: #ifndef(전통적)
  - 해당 파일이 없으면 포함하라는 의미

```cpp
// utils.h
#ifndef UTILS_H      // "UTILS_H가 정의 안 됐으면"
#define UTILS_H      // "UTILS_H를 정의해"

struct Point {
    int x;
    int y;
};

int add(int a, int b);

#endif               // 종료
```

```cpp
// 전처리 후 main.cpp
struct Point {  // 한 번만 포함
    int x;
    int y;
};
int add(int a, int b);

int main() {
    return 0;
}
```

- 방법2: #pragma once(현대적)
  - 파일을 한 번만 포함하라는 의미

```cpp
// utils.h
#pragma once

struct Point {
    int x;
    int y;
};

int add(int a, int b);
```
