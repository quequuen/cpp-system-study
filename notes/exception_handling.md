## 예외 처리 (Exception Handling)

프로그램 실해 중 발생하는 예기치 못한 상황(에러)을 감지하고 제어하는 메커니즘. 에러 처리 코드와 일반 로직을 분리하여 가독성을 향상시키지만 C++ 같은 경우, 생성자나 소멸자에서 예외가 발생할 때의 리스크(메모리 누수 등)을 반드시 고려해야 함.

- `try`: 예외가 발생할 가능성이 있는 코드 블록.
- `throw`: 예외 상황임을 알리고 예외 객체를 던짐.
- `catch`: 던져진 예외를 받아서 처리하는 블록.

```cpp
#include <iostream>
#include <string>

double divide(double a, double b) {
    if (b == 0) {
        // 에러를 발견하면 throw로 예외 객체를 던짐.
        throw std::string("0으로 나눌 수 없습니다!");
    }
    return a / b;
}

int main() {
    double x = 10, y = 0;

    try {
        double result = divide(x, y);
        std::cout << "결과: " << result << std::endl;
    }
    // 던져진 예외의 타입에 맞춰 catch가 낚아챔.
    catch (const std::string& errorMsg) {
        std::cerr << "에러 발생: " << errorMsg << std::endl;
    }

    std::cout << "프로그램이 죽지 않고 계속 실행." << std::endl;
    return 0;
}
```

- catch(...)처럼 catch 목록의 마지막에 엘립시스(Ellipsis)를 사용하면 모든 예외를 잡을 수 있지만, 구체적인 예외 타입을 명시하는 것이 좋음.

### 예외 안전성 (Exception Safety)

예외가 발생했을 때 프로그램이 안정적으로 동작하도록 보장하는 수준. C++에서는 다음과 같은 수준이 있음.

- **기본 예외 안전성**: 예외가 발생해도 프로그램이 일관된 상태를 유지하지만, 자원 누수 가능성 있음.
- **강력한 예외 안전성**: 예외가 발생하면 프로그램이 이전
  상태로 롤백되어 자원 누수 없음.
- **노예 예외 안전성**: 예외가 발생해도 프로그램이 계속 실행되지만, 상태가 일관되지 않을 수 있음.

### 스택 되감기 (Stack Unwinding)

예외가 발생하면 현재 함수의 스택 프레임이 제거되고, 소멸자들이 호출되어 자원이 해제됨. 이 과정에서 RAII(Resource Acquisition Is Initialization) 패턴이 매우 유용하게 작동하여 자원 누수를 방지함.

**예외가 던져진 지점부터 이를 잡는 catch 블록 사이의 모든 함수 호출 스택을 정리하고, 그 과정에서 생성된 지역 객체들의 소멸자를 자동으로 호출해 주는 과정.**

```cpp
class Resource {
public:
    Resource() { std::cout << "자원 획득\n"; }
    ~Resource() { std::cout << "자원 자동 해제(소멸자)\n"; }
};

void func3() {
    Resource r; // 지역 객체 생성
    throw std::runtime_error("에러 발생"); // 예외 던짐
    std::cout << "이 코드는 실행되지 않음\n";
}

void func2() { func3(); }
void func1() { func2(); }

int main() {
    try {
        func1();
    } catch (const std::exception& e) {
        std::cout << "예외 처리: " << e.what() << "\n";
    }
    return 0;
}
```

- `func3`에서 예외 발생.
- 프로그램은 `func3`을 즉시 중단하고 스택을 되감기 시작.
- 이때 `func3` 안에 있던 Resource r의 소멸자가 호출(자원 유출 방지).
- `func2`, `func1`도 차례로 종료되며 스택에서 사라짐.
- 마지막으로 main의 catch문에 도달하여 예외를 처리함.

### noexcept

함수 선언에 `noexcept`를 사용하면 해당 함수가 예외를 던지지 않을 것임을 명시적으로 나타냄. 컴파일러는 이를 최적화할 수 있으며, 예외가 발생할 경우 프로그램이 즉시 종료됨.

```cpp
void safeFunction() noexcept {
    // 이 함수는 예외를 던지지 않음
}
```

### RAII (Resource Acquisition Is Initialization)

자원 관리 기법으로, 객체의 수명과 자원의 수명을 일치시킴. 생성자에서 자원을 획득하고, 소멸자에서 자원을 해제하여 예외가 발생해도 자원 누수를 방지함. 스마트 포인터(std::unique_ptr, std::shared_ptr) 등이 RAII를 활용한 예시임.

```cpp
#include <iostream>
#include <memory>

void example() {
    // 스마트 포인터를 사용하여 동적 메모리 관리
    std::unique_ptr<int> ptr(new int(10)); // RAII로 메모리 관리

    std::cout << "값: " << *ptr << std::endl;

    // 예외가 발생해도 ptr이 소멸될 때 자동으로 메모리가 해제됨
    throw std::runtime_error("예외 발생");
}

int main() {
    try {
        example();
    } catch (const std::exception& e) {
        std::cerr << "에러: " << e.what() << std::endl;
    }

    std::cout << "프로그램이 안전하게 종료됨." << std::endl;
    return 0;
}
```
