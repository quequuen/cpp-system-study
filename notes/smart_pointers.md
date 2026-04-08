## 스마트 포인터 (Smart Pointers)

원시 포인터를 사용하면서 발생하는 문제, 수동 메모리 관리의 한계에서 벗어나기 위해 사용. 동적 할당된 메모리를 자동으로 관리하여 메모리 누수(Memory Leak)를 방지해 주는 클래스 템플릿.

- 포인터를 객체로 감싸서, 객체가 수명을 다해 사라질 때(소멸자 호출) 메모리를 **자동 해제.** (RAII 패턴)
- 널 포인터 자동 초기화 및 잘못된 메모리 접근으로 인한 버그를 줄여줌.
- 종류
  - `unique_ptr`: 특정 객체의 **단독 소유권**을 가지며 복사를 할 수 없고 오직 이동(`std::move`)만 가능.
  - `shared_ptr`: 하나의 객체를 **여러 포인터가 공동 소유할 수 있음.** 참조 횟수(Reference Count)를 관리하며, 이를 참조하는 포인터가 0이 되면 메모리를 해제함.
  - `weak_ptr`: `shared_ptr`이 관리하는 객체를 참조하지만 참조 횟수에는 영향을 주지 않음. 두 객체가 서로를 가리키는 **순환 참조(Circular Reference)** 문제를 해결.

### 무브 시맨틱 (Move Semantics)

데이터를 복사(Copy)하는 것이 아닌 이동(Move)시켜서 성능을 최적화하는 기법. 즉, 소유권만 이전하는 기술. 불필요한 메모리 할당과 복사를 줄여 프로그램의 속도를 높임.

- 우항값 참조(&&)와 std::move 사용.
  - 우항값 참조 (rvalue reference, &&)
    임시 객체만 받을 수 있는 특별한 참조자.

    ```cpp
    void func(int&& x); // 임시 숫자만 받을 수 있음.
    ```

  - std::move()
    해당 객체를 더 이상 쓰지 않으니 이동 시켜도 된다는 함수. 실제로 이동시키는 것이 아닌, 이동이 가능하도록 타입을 바꿔주는 역할.

    ```cpp
    #include <vector>
    #include <string>

    int main()
    {
        std::string str1 = "문자열1";

        // copy: str1의 내용을 str2의 메모리에 복사.
        std::string str2 = str1;

        // move: str1이 가진 문자열 메모리 주소를 str3에게 넘겨줌.
        std::string str3 = std::move(str1);

        // 해당 작업 후 str1의 내용은 비게 되고 이후로 str3가 str1의 내용을 갖게 됨.

        return 0;
    }
    ```

- `std::unique_ptr`은 **독점 소유권**을 갖기 때문에 복사가 불가능하지만 `std::move()`를 이용한 이동은 가능함.
- 또는 대용량 컨테이너의 리턴값 반환 등에서 이용됨.

### 우항값 참조(R-value Reference)

원래 기존 L-value에는 5와 같은 메모리를 가지고 있지 않은 R-value에 대해서의 참조는 하지 못함. `&&` 기호는 논리 연산자에서 쓰는 기호이지만 이런 상황에서는 임시 객체(R-value)의 주소를 담는 참조자의 용도를 가짐.

```cpp
int&& five = 5;
```

### 이동 생성자 & 이동 대입 (Move Constructor & Move Assignment)

동적 할당된 자원의 소유권을 효율적으로 이전하는 것이 목적인 생성자.

- 상대방의 포인터를 내 포인터에 복사(얕은 복사).
- 상대방의 포인터를 `nullptr`로 초기화 (자원 탈취 완료).
- 이동 대입 시에는 반드시 '자기 자신 대입'이지 확인 후, 기존 자원을 먼저 해제해야 함.

```cpp
// Resource.h

#pragma once

#include <iostream>

class Resource
{
    private:
    int* data;
    size_t size;

    public:
    Resource(size_t n);
    ~Resource();

    // 이동 생성자 (Move Constructor)
    Resource(Resource&& other) noexcept;

    // 이동 대입 연산자 (Move Assignment Operator)
    Resource& operator = (Resource&& other) noexcept;

    void printStatus() const;
};
```

```cpp
// Resource.cpp

#include "headers/Resource.h"

Resource::Resource(size_t n): size(n){
    data = new int[n];
    std::cout << "자원 생성 (크기: " << size << ")\n";
}

Resource::~Resource()
{
    delete[] data;
    std::cout << "자원 소멸\n";
}

// 이동 생성자: 얕은 복사 후 상대방 연결 끊음
Resource::Resource(Resource&& other) noexcept
// 특히 std::vector 재할당 시 중요
: data(other.data), size(other.size)
{
    other.data = nullptr;
    other.size = 0;
    std::cout << "이동 생성 완료\n";

};

Resource& Resource::operator = (Resource&& other) noexcept
{
    if (this != &other) // 자기 자신 대입 방지
    {
        delete[] data;  // 기존 자원 해제

        data = other.data;  // 상대 자원 대입
        size = other.size;

        other.data = nullptr;   // 상대 연결 끊음
        other.size = 0;
        std::cout << "이동 대입 완료\n";
    }
    return *this;
};

void Resource::printStatus() const
{
    if (data) std::cout << "데이터 존재함\n";
    else std::cout << "데이터 없음\n";
}
```

- noexcept를 쓰는 이유: 이동 중에 예외가 발생하면 시스템이 불안정해지므로, 예외를 절대 던지지 않는 것을 보장하며 컴파일러가 신뢰하고 이동을 수행할 수 있게 함. 특히 std::vector 재할당 시 중요.
- nullptr로 other을 초기화 해주는 이유: 상대방이 소멸될 때 내 데이터를 안 지우게 함. 해당 부분이 없으면 other가 소멸될 때 우리가 뺏어온 메모리까지 delete 해버림. (이중 해제 에러 발생)

```cpp
// main.cpp

#include <iostream>
#include "headers/Resource.h"
#include <vector>

int main()
{
    Resource res1(100);

    std::cout << "res1 상태: "; res1.printStatus();

    // 이동 생성자 호출 (res1의 소유권이 res2로 이동, res1은 이제 빈 값)
    Resource res2 = std::move(res1);

    std::cout << "res1 상태: "; res1.printStatus();
    std::cout << "res2 상태: "; res2.printStatus();

    Resource res3(50);
    // 이동 대입 연산자 호출 (res3가 원래 가졌던 자원은 해제되고, res2의 자원을 뺏어옴)
    res3 = std::move(res2);

    std::cout << "res1 상태: "; res1.printStatus();
    std::cout << "res2 상태: "; res2.printStatus();
    std::cout << "res3 상태: "; res3.printStatus();


    return 0;
}
```
