## functions

### 매개변수 vs 실인자 (Parameter vs Argument)

- 매개변수(Parameter): 함수 정의부에 있는 변수, 어떤 데이터를 받을지 선언하는 틀.
- 실인자(Argument): 함수를 호출할 때 실제로 전달하는 값.

### 데이터 전달 방식

데이터를 어떻게 복제하거나 연결하느냐의 차이

1. 값에 의한 전달(Call by Value)
   실인자의 값만 복사해서 매개변수에 전달.

- 메모리: 매개변수를 위한 새로운 메모리 공간이 할당, 값이 그대로 복사.
- 특징: 함수 안에서 아무리 값을 바꿔도 원본은 변하지 않음.(안전성)
- 단점: 데이터 덩어리가 클 경우, 복사하는 데 시간과 메모리가 낭비됨.

```cpp
void changeValue(int a) {
    a = 999; // 복사본만 수정됨
}

int main() {
    int x = 10;
    changeValue(x);
    // x는 여전히 10
}
```

2. 주소에 의한 전달(Call by Address)

실인자는 메모리 주소를 전달. 매개변수는 포인터 변수.

- 메모리: 주소값(일반적으로 8바이트)만 복사. 매개변수인 포인터는 원본의 주소를 가리킴.
- 특징: \* 연산자(역참조)를 통해 원본을 직접 수정 가능. nullptr을 넘길 수 있어 null 표현 가능.
- 단점: \*나 & 기호로 인해 가독성이 떨어지며 잘못된 주소를 건드릴 위험 존재.

```cpp
void changeAddress(int* ptr) {
    if (ptr != nullptr) {
        *ptr = 999; // 주소를 찾아가서 원본 수정
    }
}

int main() {
    int x = 10;
    changeAddress(&x); // 주소를 넘김
    // x는 이제 999
}
```

3. 참조에 의한 전달(Call by Reference)

실인자의 별명(Alias)를 전달. 매개변수가 원본과 이름을 공유.

- 메모리: 내부적으로는 주소를 넘기지만, 겉으로는 복사가 일어나지 않는 것처럼 보임.
- 특징: \* 기호 없이 일반 변수처럼 쓰지만 원본이 수정됨.반드시 실체가 있어야 하므로 nullptr 체크가 필요 없음.
- 단점: 함수 안에서 원본이 바뀔 수 있다는 사실이 호출부만 봐서는 명확히 드러나지 않을 수 있어 const &를 자주 씀.

```cpp
void changeReference(int &ref) {
    ref = 999; // 별명을 통해 원본 수정
}

int main() {
    int x = 10;
    changeReference(x); // 변수 그대로 넘김 (별명 붙이기)
    // x는 이제 999
}
```

| 구분          | 값(Value)              | 주소(Address)              | 참조(Reference)         |
| ------------- | ---------------------- | -------------------------- | ----------------------- |
| 매개변수 형태 | int a                  | int \*a                    | int &a                  |
| 함수 호출     | f(x)                   | f(&x)                      | f(x)                    |
| 원본 수정     | 불가능                 | 가능                       | 가능                    |
| 복사 비용     | 데이터 크기만큼        | 주소값만큼                 | 거의 없음               |
| 주요 용도     | 작은 데이터, 원본 보호 | 배열 전달, Optional한 인자 | 큰 객체 전달, 원본 수정 |

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
