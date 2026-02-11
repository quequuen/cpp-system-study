## functions

### 트레일링 반환 타입(Trailing Return Types)

C++11부터 도입된 기능으로, 함수 선언에서 반환 타입을 매개변수 리스트 뒤에 명시하는 방법. 특히 복잡한 반환 타입을 가질 때 유용하며, 함수 템플릿과 함께 자주 사용됨.

- 주요 목적
  - 반환 타입이 매개변수에 의존하는 경우
  - 복잡한 함수 포인터나 람다식 반환 타입을 명확히 할 때
  - 가독성(이름 정렬 등) 향상

```cpp
#include <iostream>

// 매개변수의 타입을 곱한 결과를 반환하는 템플릿
template <typename T, typename U>
auto combine(T a, U b) -> decltype(a + b) {
    return a + b;
}

int main() {
    auto result = combine(10, 5.5); // int + double = double
    std::cout << "결과: " << result << std::endl; // 15.5

    return 0;
}
```
