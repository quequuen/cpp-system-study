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

### 사용자 정의 예외 클래스와 상속

예외 클래스를 직접 구현 할 때에는 std::exception이나 std::runtime_error를 상속받는 것이 표준적인 방법.

- 다형성으로 인해 부모 전용 처리기에 먼저 도달 후 처리가 될 수 있으므로, 자식 전용 처리기를 반드시 더 먼저 둬야 함.
- e.what()은 어떤 catch에서 잡히든, 실제 객체인 자식이 부모 생성자에 넘겨준 메시지가 정상적으로 출력됨.

```cpp
#include <stdexcept>

// 표준 예외를 상속받아 나만의 예외 클래스 정의
class NetworkException : public std::runtime_error {
public:
    // 부모 생성자에 에러 메시지 전달
    NetworkException(const std::string& msg) : std::runtime_error(msg) {}
};

void connectServer() {
    throw NetworkException("서버 응답 시간이 초과되었습니다.");
}

int main() {
    try {
        connectServer();
    } catch (const NetworkException& e) {
        // 특정 네트워크 에러만 따로 처리
    } catch (const std::exception& e) {
        // 그 외의 모든 표준 에러 처리
    }
}
```

- connectServer() 호출 후 함수 내부에서 throw NetworkException(...) 실행으로 "서버 응답 시간이 초과되었습니다." 라는 메시지를 품은 NetworkException 객체가 메모리에 만들어지고 던져짐.
- catch에서 탐색 후, 자식 예외 클래스에 맞는 catch 도달.
- catch 블록의 실행이 끝나면 프로그램은 종료되지 않고 그 다음 코드를 계속 실행.

### Rethrowing

catch 블록 안에서 `throw;`를 사용하는 것. 방금 잡았던 예외 객체를 그대로 stack 내 다음 순서가 되는 대상에 던짐.

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

class NetworkException : public std::runtime_error {
public:
    NetworkException(const std::string& msg) : std::runtime_error(msg) {}
};

void connectServer() {
    // 예외 발생
    throw NetworkException("서버 연결 실패 (Timeout)");
}

void processNetwork() {
    try {
        connectServer();
    }
    catch (const NetworkException& e) {
        // 1차 처리: 여기서 간단한 로그만 남김.
        std::cout << "[로그 기록]: 내부 함수에서 에러 감지 -> " << e.what() << std::endl;

        // rethrow: 내부 함수에서 잡았으나 호출한 곳에 다시 던짐.
        throw;
    }
}

int main() {
    try {
        processNetwork();
    }
    catch (const NetworkException& e) {
        // 2차 처리: 최종적으로 사용자에게 에러를 알립니다.
        std::cerr << "[최종 에러 메시지]: " << e.what() << std::endl;
        std::cerr << "서버 상태를 확인하고 다시 시도해 주세요." << std::endl;
    }

    return 0;
}
```

- `throw e;`를 하게 되면 예외 객체를 복사해서 새로 던지기 때문에 이 과정에서 자식 객체를 부모 타입으로 잡고 있었다면 객체 잘림(Slicing) 현상 발생. → `throw;`로 현재 발생한 예외 객체를 그대로 위로 전달. 다형성을 완벽하게 유지하는 가장 안전한 방법.

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
