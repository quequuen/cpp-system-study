## C++ basics(C++ 기초)

C++ 기초 문서입니다. C++ 언어의 기본 문법과 개념들을 다룹니다.

### 기본 구조

```cpp
#include <iostream>
int main(){
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```


### L-values와 R-values

- L-values: 메모리 주소를 가지는 값. 변수, 배열 요소, 참조 등이 이에 해당. 대입 연산자(=)의 왼쪽에 올 수 있음.
- R-values: 값 자체를 나타내며, 메모리 주소를 가지지 않는 값. 리터럴, 임시 객체 등이 이에 해당. 대입 연산자(=)의 오른쪽에만 올 수 있음.

```cpp
int x = 10;
int y = x + 5; // x는 L-value이지만 여기서는 임시 계산 결과를 가져오기 때문에 R-value로 사용됨.

int getValue() {
    return 42;       // 42는 R-value 반환
}

int& getRef() {
    static int x = 10;
    return x;        // x의 참조 반환 (L-value)
}
```

### 초기화(initialization)와 대입(assignment)

- 초기화: 변수를 선언하면서 처음으로 값을 할당하는 과정. 초기화를 통해 변수는 메모리에 공간을 할당받게 되고 값이 설정됨. 릴리즈 모드에서는 초기화되지 않은 변수가 0으로 설정될 수 있지만, 디버그 모드에서는 쓰레기 값이 남아 있을 수 있음. 프로그램이 예측 불가능한 동작을 할 수 있으므로 초기화는 매우 중요함.
- 대입: 이미 선언된 변수에 새로운 값을 할당하는 과정. 대입은 변수의 기존 값을 새로운 값을 덮어쓰게 됨.
