## control

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
