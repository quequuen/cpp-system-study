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
