## control

### 제어 흐름(Control Flow)

프로그램이 실행되는 순서를 결정하는 아주 중요한 개념. 기본적으로 코드는 위에서 아래로 실행되지만, 제어문을 사용하면 특정 조건에 따라 코드를 건너뛰거나(분기), 특정 부분을 반복(반복)할 수 있음.

1. 조건문 (Conditional Statements)
   특정 조건의 참/거짓 여부에 따라 실행 경로를 나눔.

- if - else if - else: 가장 범용적인 조건문
  - if 내부에 단축 평가나 비트 플래그 확인 로직을 자주 사용.
- switch - case: 하나의 변수 값을 여러 상수의 값과 비교할 때 유용.

  - 주의 사항: break 문을 빠뜨리면 다음 case까지 실행되는 'Fall-through' 현상이 발생.
  - **enum class**와 함께 쓰면 가독성이 극대화됩니다.

2. 반복문 (Loops)
   특정 작업을 여러 번 되풀이할 때 사용.

- for: 반복 횟수가 명확할 때 주로 사용.
- while: 특정 조건이 만족되는 동안 계속 반복.
- do - while: 조건을 검사하기 전에 최소 한 번은 반드시 실행해야 할 때 사용.
- 주의 사항
  - **Infinite Loop**: 탈출 조건이 항상 참이 되지 않도록 주의.
  - **Off-by-one Error**: 반복 횟수가 하나 더 많거나 적게 돌아가는 실수 주의 (예: `<=` vs `<`).

3. 흐름 제어 키워드
   반복문의 흐름을 강제로 바꿀 때 사용.

- break: 현재 속해 있는 반복문이나 switch 문을 즉시 탈출.
- continue: 반복문의 나머지 코드를 건너뛰고 바로 다음 반복(조건 검사)으로 넘김.
- return: 함수 자체를 종료하고 호출한 곳으로 값을 반환.

4. 예외 처리 (Exceptions)
   예상치 못한 상황(에러)이 발생했을 때 프로그램이 갑자기 꺼지지 않도록 하는 우회로.

- try: 에러가 발생할 가능성이 있는 코드를 블록으로 감싸 일단 시도.
- throw: 에러가 발생할 시, 에러 객체(메시지나 번호)를 던짐.
- catch: 던져진 에러를 받아 처리.(프로그램이 종료되지 않게 실질적으로 막는 지점.)

  ```cpp
  #include <iostream>
  #include <string>

  void checkAge(int age) {
      if (age < 0) {
          throw std::string("나이는 음수일 수 없습니다!"); // 예외를 던짐
      }
      std::cout << "나이 확인 완료: " << age << std::endl;
  }

  int main() {
      try {
          checkAge(-5); // 예외 발생
      }
      catch (const std::string& errorMsg) { // 던져진 문자열을 받음
          std::cerr << "에러 발생: " << errorMsg << std::endl;
      }

      std::cout << "프로그램이 정상 종료되었습니다." << std::endl;
      return 0;
  }
  ```

5. 중단 (Halt)
   코드 실행 중 심각한 오류가 발생했거나, 의도적으로 프로세스를 즉시 종료해야 할 때 사용. 더 큰 의미에서는 프로그램의 실행을 강제로 멈추거나, CPU가 더 이상 명령어를 수행하지 않는 상태.

- std::exit(): 프로그램을 정상적으로 종료. 파괴자(Destructor)를 호출하고 리소스를 정리한 뒤 종료.
- std::abort(): 비정상적인 종료를 유도. 리소스를 정리하지 않고 즉시 프로세스를 끝내며, 보통 에러 로그(core dump)를 남길 때 사용.
- std::terminate(): 주로 예외 처리(try-catch) 중 더 이상 예외를 처리할 수 없을 때 시스템에 의해 호출.

### 리소스 정리

프로그램이 실행되는 동안 시스템(OS)로부터 빌려 썼던 자원들을 사용이 끝난 뒤 다시 시스템에 돌려주는 과정.

1. 정리해야 할 리소스의 종류

- 메모리 (Memory): new나 malloc으로 할당받은 동적 메모리.
- 파일 핸들 (File Handles): 읽거나 쓰기 위해 열러둔 파일.
- 네트워크 소켓(Network Sockets): 읽거나 쓰기 위해 열어둔 파일.
- 뮤텍스/락(Mutex/Locks): 멀티스레딩에서 자원 독점권을 위해 걸어둔 잠금장치.

2. 리소스 누수(Resource Leak)

리소스를 제때 돌려주지 않는 것.

- 메모리 누수(Memory Leak): 프로그램이 메모리를 계속 차지하여 시스템 전체가 느려지거나, 결국 메모리 부족으로 프로그램이 강제 종료됨.
- 파일/소켓 부족: 시스템이 한 프로세스에 허용하는 파일 오픈 개수는 제한되어 있음. 정리를 안하면 나중에 파일을 열려고 해도 열 수 없는 에러가 발생.

3. C++에서 리소스를 정리하는 법

- 수동 정리
  개발자가 직접 정리하는 것을 명시하는 방식.

  - new로 빌렸으면 delete로 반납.
  - fopen으로 파일을 열었으면 fclose로 닫기.
  - 중간에 return을 하거나 예외(throw)가 발생하면 반납 코드까지 도달하지 못해 누수가 생길 위험 존재.

- 자동 정리
  객체가 사라진 때 호출되는 파괴자(Destructor)에 반납 로직을 넣는 것.
  - 스마트 포인터(std::unique_ptr 등): 메모리를 알아서 해제.
  - std::fstream: 변수가 범위를 벗어나면 파일을 알아서 닫아줌.

### 논리 연산자

논리 연산자는 bool 타입의 값들을 조합하여 복잡한 조건식을 만들 때 사용됨.

- AND 연산자 (&&)
  - 두 피연산자가 모두 true일 때만 결과가 true.
- OR 연산자 (||)
  - 두 피연산자 중 하나라도 true이면 결과가 true.
- NOT 연산자 (!)
  - 피연산자의 논리 값을 반전시킴. true는 false로, false는 true로 바꿈.

```cpp
#include <iostream>

int main()
{
    using namespace std;

    bool a = true;
    bool b = false;

    cout << "a AND b: " << (a && b) << endl; // false
    cout << "a OR b: " << (a || b) << endl;  // true
    cout << "NOT a: " << (!a) << endl;       // false

    return 0;
}
```

- 증감 연산자와 함께 사용할 경우, 우선순위에 주의해야 함.

```cpp
#include <iostream>

int main()
{
    using namespace std;

    int x = 10;
    int y = 20;

    if (x == 10 && y++ == 20)
    // 좌항이 true이기 때문에 y가 21로 증가
    // 좌항이 false였다면 y는 증가하지 않았을 것.
    // 해당 조건문이 || 연산자였다면 y는 증가하지 않았을 것. 반대로 좌항이 false인 || 연산자였다면 y는 증가했을 것.
    {
        cout << "Inside if block." << endl;
    }

    cout << "y: " << y << endl;


    return 0;
}
```

- 주의 사항: Logical And가 Logical Or보다 우선순위가 높음. 복잡한 논리식을 작성할 때는 괄호를 사용하여 명확하게 표현하는 것이 좋음.

### 단축 평가(Short-Circuit Evaluation)

- **&& (AND) 논리 곱 연산자:** 좌항이 false이면, 우항이 무엇이든 결과는 무조건 false(좌항이 거짓이면 우항은 평가하지 않음).
- **|| (OR) 논리 합 연산자:** 좌항이 true이면, 우항이 무엇이든 결과는 무조건 true(좌항이 참이면 우항은 평가하지 않음).

```cpp
#include <iostream>

int main()
{
    using namespace std;

    int x = 0;

    // AND 연산자에서 좌항이 false이므로 우항은 평가되지 않음.
    if (false && (++x > 0)) {
        // 실행되지 않음
    }
    cout << "After AND short-circuit, x: " << x << endl; // x는 0

    // OR 연산자에서 좌항이 true이므로 우항은 평가되지 않음.
    if (true || (++x > 0)) {
        // 실행됨
    }
    cout << "After OR short-circuit, x: " << x << endl; // x는 여전히 0

    // 앞의 (10 > 5)가 참이므로 뒤의 함수는 호출조차 되지 않음!
    bool result = (10 > 5) || (ptr->doSomething());

    return 0;
}

```

- 첫번째 예시
  - 포인터가 비어있는데(nullptr) 내부 값을 참조하면 프로그램이 즉시 종료(Crash)됨. 단축 평가를 써서 해당 문제를 방지할 수 있음.

```cpp
// ptr이 nullptr이면 (ptr != nullptr)이 false가 되어
// 뒤의 ptr->data는 확인조차 안 하므로 안전하게 동작함.
if (ptr != nullptr && ptr->data > 10)
{
    // 로직 실행
}
```

- 두번째 예시
  - 배열의 인덱스가 범위를 벗어나는지 먼저 확인한 뒤, 값을 검사할 때 사용.

```cpp
// index가 max_size보다 크면 array[index]를 읽지 않으므로 안전하게 동작함.
if (index < max_size && array[index] == target) {
    // 로직 실행
}
```

- Side Effect 주의

  - 단축 평가를 사용할 때, 우항에 부수 효과(Side Effect)가 있는 코드를 넣지 않도록 주의해야 함. 우항이 평가되지 않을 수도 있기 때문임.
  - 논리 연산자의 우항에는 상태를 변경하는 중요한 함수나 연산(증감 연산 등)을 넣지 않는 것이 가독성과 안전성 측면에서 좋음.

### 산술 연산자(Arithmatic Operaters)

| 연산자 | 기능           | 예시 (int a=7, b=3)  | 결과 |
| ------ | -------------- | -------------------- | ---- |
| +      | 덧셈           | a + b                | 10   |
| -      | 뺄셈           | a - b                | 4    |
| \*     | 곱셈           | a \* b               | 21   |
| /      | 나눗셈         | a / b                | 2    |
| %      | 나머지         | a % b                | 1    |
| +=     | 덧셈 후 대입   | a += b (a = a + b)   | 10   |
| -=     | 뺄셈 후 대입   | a -= b (a = a - b)   | 4    |
| \*=    | 곱셈 후 대입   | a \*= b (a = a \* b) | 21   |
| /=     | 나눗셈 후 대입 | a /= b (a = a / b)   | 2    |
| %=     | 나머지 후 대입 | a %= b (a = a % b)   | 1    |

### 증감 연산자(Increment and Decrement Operators)

- ++ : 변수의 값을 1 증가시킴.
- -- : 변수의 값을 1 감소시킴.
- 전위 연산자(Pre-increment/Pre-decrement): 대상이 되는 값을 먼저 증가/감소시킨 후, 그 값을 반환함.
- 후위 연산자(Post-increment/Post-decrement): 대상이 되는 값을 먼저 반환한 후, 그 값을 증가/감소시킴. **줄이 바뀌는 시점에** 값이 변함.

```cpp
#include <iostream>
int main()
{
    using namespace std;

    int x = 5;

    cout << "Initial x: " << x << endl; // 5

    cout << "Post-increment x++: " << x++ << endl; // 5
    cout << "After post-increment, x: " << x << endl; // 6

    cout << "Pre-increment ++x: " << ++x << endl; // 7
    cout << "After pre-increment, x: " << x << endl; // 7

    cout << "Post-decrement x--: " << x-- << endl; // 7
    cout << "After post-decrement, x: " << x << endl; // 6

    cout << "Pre-decrement --x: " << --x << endl; // 5
    cout << "After pre-decrement, x: " << x << endl; // 5

    return 0;
}
```

### 쉼표 연산자(Comma Operator)

쉼표(,) 연산자는 두 개의 표현식을 평가하고, 두 번째 표현식의 결과를 반환함.

```cpp
#include <iostream>
int main()
{
    using namespace std;

    int a = 5;
    int b = 10;

    int result = (a += 2, b += 3); // a는 7이 되고, b는 13이 됨. result는 b의 값인 13이 됨.
    int d = (++a, b--); // a는 8이 되고, b는 12가 됨. d는 b의 값인 12가 됨.
    int e;
    e = a, b; // e는 b의 값인 12가 됨.

    cout << "a: " << a << endl;         // 8
    cout << "b: " << b << endl;         // 12
    cout << "result: " << result << endl; // 13
    cout << "d: " << d << endl;         // 12
    cout << "e: " << e << endl;         // 12

    return 0;
}
```

- 주의: 쉼표 연산자는 가독성을 떨어뜨릴 수 있으므로, 복잡한 표현식에서는 사용을 피하는 것이 좋음.

### 조건 연산자(Conditional Operator)

조건 연산자(삼항 연산자)는 세 개의 피연산자를 가지며, 조건에 따라 두 값 중 하나를 선택함.

- 조건식 ? 참일 때 값 : 거짓일 때 값
- 값들의 타입은 동일해야 함.
- 해당 연산자는 if-else 문을 간단하게 표현할 때 유용하지만 복잡한 로직에서의 사용은 가독성을 떨어뜨릴 수 있음.
- 사용할 때 연산자의 우선순위를 주의해야 함.

```cpp
#include <iostream>
int main()
{
    using namespace std;

    int a = 5;
    int b = 10;

    int max = (a > b) ? a : b;

    cout << "Max: " << max << endl;

    return 0;
}
```

### 관계 연산자(Relational Operators)

관계 연산자는 두 값을 비교하여 참(true) 또는 거짓(false)을 반환함.
| 연산자 | 기능 | 예시 (int a=5, b=10) | 결과 |
| ------ | ------------ | --------------------- | ----- |
| == | 같음 | a == b | false |
| != | 같지 않음 | a != b | true |
| > | 큼 | a > b | false |
| < | 작음 | a < b | true |
| >= | 크거나 같음 | a >= b | false |
| <= | 작거나 같음 | a <= b | true |

```cpp
#include <iostream>
int main()
{
    using namespace std;

    int a = 5;
    int b = 10;

    cout << "a == b: " << (a == b) << endl; // false
    cout << "a != b: " << (a != b) << endl; // true
    cout << "a > b: " << (a > b) << endl;   // false
    cout << "a < b: " << (a < b) << endl;   // true
    cout << "a >= b: " << (a >= b) << endl; // false
    cout << "a <= b: " << (a <= b) << endl; // true

    return 0;
}
```

- 주의 사항
  - 관계 연산자는 피연산자의 타입이 다를 경우 암묵적 형변환이 발생할 수 있으므로, 비교하려는 값들의 타입이 일치하는지 확인하는 것이 좋음.
  - 부동소수점 타입(float, double 등)을 비교할 때는 오차 문제로 인해 예상치 못한 결과가 나올 수 있으므로, 직접적인 비교보다는 일정 범위 내에서의 비교를 권장함.
  - NaN(Not a Number) 값은 자기 자신과도 같지 않음. 즉, (nan == nan)은 false를 반환함.

```cpp
#include <iostream>
int main()
{
    double my_d1 = 0.1 + 0.1 + 0.1;
    double my_d2 = 0.3;

    const double epsilon = 1e-10; // 허용 오차 범위

    if (std::abs(my_d1 - my_d2) < epsilon)
    {
        cout << "my_d1 and my_d2 are considered equal." << endl;
    }
    else
    {
        cout << "my_d1 and my_d2 are NOT equal." << endl;
    }

    return 0;
}
```

### 비트 연산자(Bitwise Operators)

비트 연산자는 정수형 데이터의 비트 단위로 연산을 수행함.

| 연산자 | 기능          | 예시 (int a=5, b=3) | 결과 |
| ------ | ------------- | ------------------- | ---- |
| &      | 비트 AND      | a & b               | 1    |
| \|     | 비트 OR       | a \| b              | 7    |
| ^      | 비트 XOR      | a ^ b               | 6    |
| ~      | 비트 NOT      | ~a                  | -6   |
| <<     | 왼쪽 시프트   | a << 1              | 10   |
| >>     | 오른쪽 시프트 | a >> 1              | 2    |

```cpp
#include <iostream>
int main()
{
    using namespace std;
    int a = 5;  // 0101
    int b = 3;  // 0011
    cout << "a & b: " << (a & b) << endl;   // 0001 -> 1
    cout << "a | b: " << (a | b) << endl;
    cout << "a ^ b: " << (a ^ b) << endl;   // 0110 -> 6
    cout << "~a: " << (~a) << endl;         // 1010 -> -6 (2의 보수 표현)
    cout << "a << 1: " << (a << 1) << endl; // 1010 -> 10
    cout << "a >> 1: " << (a >> 1) << endl; // 0010 -> 2
    return 0;
}
```

- 제곱이나 배수를 빠르게 계산할 때 유용함.

  - 예: x \* 2는 x << 1로, x \* 4는 x << 2로 대체 가능.

- 주의 사항
  - 비트 연산자는 주로 저수준 프로그래밍, 임베디드 시스템, 성능 최적화 등에 사용됨.
  - 음수에 대한 비트 연산은 2의 보수 표현을 사용하므로 예상치 못한 결과가 나올 수 있음.
  - 비트 시프트 연산자는 부호 있는 정수형에서 사용 시, 부호 비트가 유지되는지 여부에 따라 결과가 달라질 수 있음.

### 비트 플래그(Bit Flags)

비트 플래그는 하나의 정수형 변수 내에서 여러 개의 불리언 상태를 저장하는 방법임. 각 비트는 독립적인 상태를 나타냄.

```cpp
#include <iostream>

// 각 비트 자리에 의미를 부여 (2의 거듭제곱)
const unsigned char opt_moving   = 1 << 0; // 0000 0001
const unsigned char opt_attacking = 1 << 1; // 0000 0010
const unsigned char opt_jumping   = 1 << 2; // 0000 0100

int main()
{
    using namespace std;

    unsigned char my_status = 0; // 초기 상태 (전부 off)

    // 상태 추가 (OR 연산)
    my_status |= opt_moving;
    my_status |= opt_jumping;

    // 상태 확인 (AND 연산)
    if (my_status & opt_moving) std::cout << "이동 중입니다." << std::endl;

    // 상태 제거 (AND + NOT 연산)
    my_status &= ~opt_jumping;

    return 0;
}
```

### 비트 마스크(Bit Masks)

비트 마스크는 특정 비트들을 선택적으로 조작하기 위해 사용되는 값임. 주로 비트 플래그와 함께 사용됨.

```cpp
#include <iostream>
#include <iomanip>

int main() {
    // 32비트 컬러 값 (0xRRGGBBAA)
    // 예: 주황색 계열 (Red: FF, Green: A5, Blue: 00, Alpha: FF)
    uint32_t orange_pixel = 0xFFA500FF;

    // 비트 마스크 정의 (각 색상 위치만 1로 채움)
    uint32_t red_mask   = 0xFF000000;
    uint32_t green_mask = 0x00FF0000;
    uint32_t blue_mask  = 0x0000FF00;

    // 마스크를 이용한 색상 추출
    // 1. AND 연산으로 해당 비트만 남김
    // 2. 비트 이동(Shift)으로 값을 맨 오른쪽으로 밀어서 정수로 만듦
    uint32_t r = (orange_pixel & red_mask) >> 24;
    uint32_t g = (orange_pixel & green_mask) >> 16;
    uint32_t b = (orange_pixel & blue_mask) >> 8;

    std::cout << "Red: "   << std::hex << r << std::endl; // ff
    std::cout << "Green: " << std::hex << g << std::endl; // a5
    std::cout << "Blue: "  << std::hex << b << std::endl; // 00

    return 0;
}
```

### 비트 플래그 vs 비트 마스크

- 비트 플래그: "이 비트가 1이야, 0이야?" **개별 스위치 조작**
- 비트 마스크: "이 큰 값에서 내가 원하는 부분만 잘라낼 거야." **데이터 추출**

### 조건문(Selection)

- if - else if - else
  가장 기본이 되는 분기문.

  ```cpp
  int score = 85;
  if (score >= 90) std::cout << "A";
  else if (score >= 80) std::cout << "B"; // 실행됨
  else std::cout << "C";
  ```

  - 조건식 결과는 반드시 bool 타입이어야 함.
  - 조건식에는 비교 연산자가 아닌 대입 연산자(=)를 쓰게 되면 해당 변수에 값을 대입 후 항상 true 처리.

- switch - case
  하나의 변수 값을 여러 고정된 상수와 비교할 때 사용.

  ```cpp
  enum class State { Run, Stop };
  State s = State::Run;
  switch (s) {
    case State::Run: std::cout << "Running..."; break;
    case State::Stop: std::cout << "Stopped"; break;
  }
  ```

  - 각 case 끝에 break를 넣지 않으면 아래쪽 case까지 실행되는 **Fall-through** 현상 발생.

### 반복문(Iteration)

- while
  조건이 참인 동안 계속 실행.

  ```cpp
  int i = 0;
  while (i < 3) {
    std::cout << i << " "; // 0 1 2
    i++;
  }
  ```

  - 루프 안에서 조건을 변화시키지 않으면 무한 루프(Infinite Loop)에 빠져 프로그램이 응답 없음 상태가 됨.

- do - while
  조건을 나중에 검사하므로, 최소 1번은 무조건 실행.

  ```cpp
  int i = 10;
  do {
    std::cout << "한 번은 실행됨";
  } while (i < 5);
  ```

  - while 문 끝에 세미콜론(;)을 반드시 붙여야 함.

- for
  반복 횟수가 정해져 있을 때 가장 좋은 선택

  ```cpp
  for (int i = 0; i < 5; ++i) {
    std::cout << i; // 01234
  }
  ```

  - 루프 변수 i는 for문 안(지역 범위)에서만 유효.

### 점프문(Jump)

- break
  반복문이나 switch문을 즉시 탈출.

  ```cpp
  for (int i = 0; i < 10; i++) {
    if (i == 5) break; // 5가 되면 루프 종료
    std::cout << i;
  }
  ```

- continue
  현재 반복의 남은 코드를 건너뛰고 다음 반복(증감/조건 검사)으로 즉시 점프.

  ```cpp
  for (int i = 0; i < 5; i++) {
    if (i % 2 == 0) continue; // 짝수면 건너뜀
    std::cout << i; // 1, 3 출력
  }
  ```

- goto
  코드의 실행 흐름을 조건 없이 특정 레이블(Label)이 지정된 위치로 즉시 이동.

  ```cpp
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
        if (심각한_에러_발생) {
            goto error_handler;
        }
    }
  }

  error_handler:
  std::cerr << "에러를 처리하고 중단합니다." << std::endl;
  ```

  - 스파게티 코드, 가독성 및 유지보수 저하, 대안 존재(break, return, exception 등), 객체 생성 건너뛰기 금지와 같은 이유로 현재는 사용을 금지하거나 지양함.
  - 중첩 루프의 일괄 탈출 등 극히 제한적인 상황에서만 사용.
