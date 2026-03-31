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
