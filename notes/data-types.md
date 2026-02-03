## data types

기본 자료형의 종류, 크기(byte), 범위, 형변환(Type Casting) 등 자료형에 특화된 깊이 있는 내용을 정리합니다.

### 기본 자료형(Primitive Data Types)

C++의 기본 자료형(Primitive Data Types)은 데이터를 메모리에 저장하는 가장 기초적인 단위. 용도, 크기(Size), 범위(Range)를 중심으로 이해하는 것이 핵심.

1. 정수형(Integer Types)

   소수점이 없는 정수를 저장. 시스템(32bit vs 64bit)에 따라 크기가 다를 수 있지만, 현대적인 환경에서의 일반적인 크기는 다음과 같음.

| 자료형    | 크기 (Typical) | 범위 (약)                | 용도                          |
| --------- | -------------- | ------------------------ | ----------------------------- |
| char      | 1 byte         | -128 ~ 127               | 문자 한 개 저장 (ASCII 코드)  |
| short     | 2 bytes        | -32,768 ~ 32,767         | 작은 범위의 정수              |
| int       | 4 bytes        | -21억 ~ 21억             | 가장 일반적으로 사용되는 정수 |
| long long | 8 bytes        | $-9.22 \times 10^{18}$ ~ | 매우 큰 정수                  |

- Tip: 부호가 없는 정수를 쓰고 싶다면 앞에 **unsigned**를 붙임. (예: unsigned int). 이 경우 음수는 저장 못 하지만 양수의 범위가 2배로 늘어남.

2. 실수형(Floating-point Types)

   소수점이 있는 숫자를 저장함. 부동 소수점 방식을 사용하여 정밀도를 결정.

- float(4 bytes): 소수점 아래 약 7자리까지 유효함. 메모리 절약이 필요할 때 사용. 사용 시에는 숫자 뒤에 'f'를 붙여 명시하는 습관이 좋음. 'f' 제거 후 대입 시, double로 인식되어 Truncation Warning이 발생.

```cpp
float myFloat = 3.14f;
```

- double(8 bytes): 소수점 아래 약 15자리까지 유효함. C++에서 실수의 기본형이며 가장 권장됨.
- long double(8 bytes 이상): 더 높은 정밀도가 필요할 때 사용. 환경에 따라 double과 같을 수 있음.

3. 논리형 및 기타 (Boolean & Others)

- bool(1 bytes): true(참) 또는 false(거짓)만 저장.
  - C ++에서는 0은 거짓, 0이 아닌 모든 수는 참으로 처리.
- void: "값이 없음"을 의미함. 주로 리턴값이 없는 함수의 타입으로 사용.

- Tip: 모든 자료형은 sizeof() 연산자를 사용하면 실제 바이트 크기를 얻을 수 있음.

### 타입 추론

컴파일러가 프로그래머를 대신하여 변수의 데이터 타입을 결정하는 기능. 명시적인 타입 선언(예: int, double) 대신 키워드를 사용하여 코드를 간결하게 만들고, 복잡한 타입 구조에서 발생할 수 있는 오류를 줄여줌.

1. auto

   선언된 변수의 **초기화 값(Initializer)**을 보고 컴파일러가 타입을 추론하게 함. 반드시 선언과 동시에 초기화를 해야 함. 가독성을 높이고, 특히 반복자(Iterator)나 템플릿처럼 타입명이 매우 길 때 유용.

- 주의: const나 참조(&)속성을 기본적으로는 떼어내고 추론하는 경향이 있음. (const auto&처럼 명시 가능)

```cpp
auto i = 10;          // int
auto d = 3.14;        // double
auto s = "Hello";     // const char*
```

2. decltype

   "declared type"의 줄임말로, 주어진 식(expression)의 타입을 컴파일 타임에 알아내어 그대로 사용 가능하게 함. auto와 달리 초기화 값이 없어도 타입만 선언 가능하며 참조(&)나 상수성(const) 등 원래 타입이 가진 성질을 그대로 유지함.

```cpp
int x = 10;
decltype(x) y = 20; // x의 타입인 int를 추론하여 y를 int로 선언
```

- 주로 템플릿 프로그래밍이나 함수의 반환 타입을 지정할 때 사용.

### auto vs decltype

```cpp
int x = 10;
int& ref = x;

auto a = ref;          // a는 int (참조가 사라짐)
decltype(ref) b = x;   // b는 int& (참조가 유지됨)
```

| 구분      | auto                       | decltype                   |
| --------- | -------------------------- | -------------------------- |
| 추론 기준 | 우변의 값에 기반           | 명시된 식/변수 자체에 기반 |
| 초기화    | 필수                       | 불필요                     |
| 속성 유지 | 기본 속성(int 등)만 가져옴 | const, & 등 모든 속성 유지 |

### 초기화 방법 (initializtion)

C++에서 변수를 초기화하는 방법은 크게 세가지로 나뉨.

1. Copy Initialization(복사 초기화)

   가장 익숙한 = 기호를 사용하는 방식.

- 우변의 값을 좌변의 변수에 복사하여 넣는 개념.
- 클래스 객체에서는 성능 최적화가 일어나기도 하지만, 원칙적으로는 복사 생성자를 호출하는 방식.

2. Direct Initialization(직접 초기화)

   괄호 ()를 사용하여 명시적으로 값을 전달.

- 복사 과정 없이 메모리에 바로 값을 넣는 느낌.
- 주로 생성자가 있는 객체를 초기화할 때 많이 쓰임.
- **Most Vexing Parse**라는 문제 발생 가능성 높음. 컴파일러가 변수 선언을 함수 선언으로 착각하는 경우가 있음.

3. Uniform Initialization(균일한 초기화 or 중괄호 초기화)

   중괄호 {}를 사용하는 방식. **가장 권장되는 방식**

- Narrowing Castiong 방지: 데이터 손실이 발생하는 형변환을 컴파일 단계에서 막아줌.
- 일관성: 변수, 배열, 구조체, 클래스 어디에서나 동일한 문법을 쓸 수 있음.
- 함수 착각 방지: 위에서 언습한 Direct Initialization의 함수 오인 문제를 완벽히 해결함.

```cpp
// 1. Copy Initialization
int copy_init = 10;

// 2. Direct Initialization
int direct_init(20);

// 3. Uniform Initialization (현대적 권장 방식)
int uniform_init{30};

// int x = 3.14;   // 컴파일 됨 (데이터 손실 발생, 3으로 저장)
// int y{3.14};    // 컴파일 에러! (데이터 손실로부터 보호해줌)
```

### 오버플로우 (overflow)

변수에 할당된 메모리 공간이 표현할 수 있는 한계 범위를 초과하는 값을 저장하려고 할 때 발생하는 현상.

1. 오버플로우의 원리: 순환(Wrapping)

```cpp
int a = 255;
a = a + 1;
cout << a << endl;
// a의 값은 256이 아닌 최소값인 0으로 돌아감.
```

자동차의 주행거리계(Odometer)가 99,999km를 찍고 다시 0으로 돌아가는 것과 같다고 해서 **"Wrapping"** 현상이라고 부름.

2. 부호 있는 정수(Signed) vs 부호 없는 정수(Unsigned)

   1. Usigned Integer(부호 없음)

   - 표준에 의해 정의된 동작(Defined Behavior)
   - 최대값을 넘으면 0부터 다시 시작하고, 0에서 1을 빼면(Underflow) 최대값으로 돌아감.
   - unsigned int max = 4294967295; max +1 은 정확히 0이 됨.

   2. Signed Integer(부호 있음)

   - 표준에 의해 정의되지 않은 동작(undefined Behavior)
   - 최대값을 넘기면 보통은 가장 작은 음수로 뒤집히거나 컴파일러나 OS 환경에 따라 프로그램이 강제 종료되거나 예상치 못한 결과가 나올 수 있어 매우 위험.

3. 발생 원인과 위험성

   - 발생 원인

     - 사용자 입력: 예상보다 너무 큰 숫자를 입력받을 때.
     - 누적 계산: 반복문 안에서 합계를 구할 때 변수의 한계를 고려하지 않은 경우.
     - 형변환: 큰 타입을 작은 타입으로 강제 변환할 때.

   - 위험성(보안 이슈)

     - 무한 루프: 반복문의 제어 변수가 오버플로우로 인해 조건식을 영원히 만족하게 될 가능성 있음.
     - 메모리 손상: 배열의 인덱스 계산 시 오버플로우가 나면 엉뚱한 메모리 위치를 참조하게 되어 해킹의 경로가 될 수 있음.

4. 실전 예제 및 방지법(limits 활용)

```cpp
#include <iostream>
#include <limits>

int main() {
    int max = std::numeric_limits<int>::max();
    int a = 1;

    // 오버플로우 발생 전 미리 체크하기
    // 논리적 체크 예시
    if (a > 0 && max - a < 0) {
        std::cout << "오버플로우 위험!" << std::endl;
    } else {
        std::cout << "안전한 계산: " << max + a << std::endl; // 실제로는 여기서 오버플로우 발생
    }

    return 0;
}
```

### 고정 너비 정수(Fixed-width Integers)

시스템이나 아키텍처(32 비트, 64 비트 등)에 상관없이 변수의 크기를 비트(bit) 단위로 정확하게 고정하고 싶을 때 사용.
원래 C++의 기본 자료형인 int나 long은 컴파일러나 운영체제에 따라 크기가 달라질 수 있다는 불완전함이 있는데, 이를 해결하기 위해 등장.

- Portability 이슈

  - 컴퓨터나 운영체제에 따라 자료형의 크기가 다름.
  - 데이터 정밀도: 네트워크 통신이나 파일 저장 시, 정확히 4 바이트 데이터를 보내야 하는데 int 크기가 달라지면 데이터가 깨지게 됨.

- 종류
  | 자료형(Signed) | 자료형(Unsigned) | 크기(Bit) |크기(Byte) |
  | --------- | -------------------------- | -------------------------- |-------------------------- |
  | int8_t | uint8_t | 8 bits | 1 byte |
  | int16_t | uint16_t | 16 bits | 2 byte |
  | int32_t | uint32_t | 32 bits | 4 byte |
  | int64_t | uint64_t | 64 bits | 8 byte |

```cpp
#include <iostream>
// #include <cstdint>
// 고정 너비 정수형을 위한 헤더는 cstdint지만 요즘은 iostream 내에서 cstdint를 include 하고 있음.

int main()
{
    using namespace std;
    // 시스템에 상관없이 무조건 32비트(4바이트)를 차지함.
    int32_t myFixedInt = 1000;

    // 무조건 64비트(8바이트)
    uint64_t myHugeInt = 0xFFFFFFFFFFFFFFFF;
    cout << "size: " << sizeof(myFixedInt) << " bytes" << endl;
    cout << "size: " << sizeof(myHugeInt) << " bytes" << endl;

    return 0;
}
```

- \_fast와 \_least
  <cstdint>에는 더 정밀한 제어를 위한 변형 타입도 존재.
  - int_fast32_t: 최소 32비트를 보장하면서, 내 컴퓨터에서 **가장 빠르게 처리되는** 타입을 선택.
  - Int_least32_t: 최소 32비트를 가질 수 있는 **가장 작은** 타입을 선택.
