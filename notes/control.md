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

- **&& (AND):** 좌항이 거짓이면 우항은 평가하지 않음.
- **|| (OR):** 좌항이 참이면 우항은 평가하지 않음.

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
