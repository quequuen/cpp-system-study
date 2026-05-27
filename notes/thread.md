## thread

### **프로세스 (Process)**

운영체제에서 메모리에 올라와 실행 중인 프로그램. 각 프로세스는 독립된 메모리 공간(코드, 데이터, 힙 등)을 갖음.

### **스레드 (Thread)**

프로세스 안에서 실제로 작업을 수행하는 실행 흐름의 단위. 같은 프로세스 내의 스레드들은 메모리(자원)를 서로 공유하며 작동함. 2개 이상의 스레드가 프로세스 내부에 존재하는 것을 멀티 스레드 프로세스하고 함.

- 메모리 관점에서 본 스레드의 특징
  - 공유하는 영역: 데이터(Data) 영역, 힙(Heap) 영역.
    - 특징: 전역 변수나 동적 할당된 메모리는 모든 스레드가 다 같이 접근하고 수정할 수 있음. 주소록을 같이 쓰는 것과 같아서 서로 소통하기 편하지만, 동시에 수정하려 들면 데이터가 꼬이는 위험(`Data Race`)이 있음.
  - 독립적인 영역: 스택(Stack) 영역.
    - 특징: 스레드는 각자 자기만의 실행 대기열과 지역 변수를 가짐. 이 영역은 다른 스레드가 절대 건드릴 수 없는 독립된 공간.

### **멀티 스레드 (Multi-thread)**

하나의 프로세스 안에 여러 개의 스레드를 만들어 여러 작업을 동시에 처리하는 방식.

- 장점: 여러 작업을 병렬로 처리하여 빠르게 처리할 수 있고 자원을 효율적으로 사용할 수 있음.
- 단점: 자원을 공유하기 때문에 하나의 스레드에 문제가 생기면 프로세스 전체에 영향을 줄 수 있음. 설계가 복잡함.

### 컨텍스트 스위칭 (Context Switching)

CPU 코어는 한 번에 하나의 스레드만 처리할 수 있음. 그래서 스레드를 바꿀 때, 기존 하던 일의 상태를 저장하고 다음 상태를 불러오는 작업을 하는데 이를 컨텍스트 스위칭이라고 함. 하지만 이 작업이 너무 자주 일어나게 되면 컴퓨터가 쉽게 지침.

### 동기화 (Synchronization)

여러 스레드가 공용 변수를 건드릴 때 순서를 정리해주는 기술.

### 교착 상태 (Deadlock)

두 개 이상의 스레드가 서로 상대방의 자원이 풀리기만을 기다리며 무한히 대기하는 상태. 서로 양보하지 않아서 프로그램이 그 자리에 얼어붙어 버리는(Freeze) 현상.

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtxA;
std::mutex mtxB;
// 한 자물쇠 당 하나만 잠글 수 있음.

void worker1() {
    mtxA.lock(); // A를 먼저 잠금
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 잠시 대기 (강제로 lock 발생시키려고)
    mtxB.lock(); // B를 잠그려고 보니 이미 worker2에서 사용 (무한 대기)

    std::cout << "worker 1 업무 완료!" << std::endl;
    mtxB.unlock();
    mtxA.unlock();
}

void worker2() {
    mtxB.lock(); // B를 먼저 잠금
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    mtxA.lock(); // A를 잠그려고 보니 이미 worker1에서 사용 (무한 대기)

    std::cout << "worker2 업무 완료!" << std::endl;
    mtxA.unlock();
    mtxB.unlock();
}
```

- `std::mutex`: Mutual Exclusion(상호 배제)의 약자로, 여러 스레드가 공유 자원에 동시에 접근하지 못하도록 막는 동기화 도구.
- worker1이 A를 쥐고 B를 원함 → worker2이 B를 쥐고 A를 원함 → 프로그램은 이 지점에서 멈춰버리고 다음 코드로 넘어가지 못함. (deadlock 발생)
- 교착 상태가 성립하는 4가지 조건
  교착 상태는 다음 4가지 조건이 동시에 만족할 때만 발생. 역으로 말하면 이 중 하나라도 부수면 교착 상태를 예방할 수 있음.
  - **상호 배제 (Mutual Exclusion)**: 한 번에 한 스레드만 자원을 사용 가능.
  - **점유와 대기 (Hold and Wait)**: 자원 하나를 쥔 상태(`Hold`)에서 다른 자원을 달라고 기다림(`Wait`).
  - **비선점 (No preemption)**: 다른 스레드가 쥐고 있는 자원을 강제로 뺏어올 수 없음.
  - **순환 대기 (Circular Wait)**: 대기 관계가 원형 모양으로 꼬여있음 (A→B, B→A).

- 해결 방법
  - `std::lock`
    교착 상태는 한 마디로 잠그는 순서가 서로 달라서 발생. 그렇기 때문에 가장 쉽고 확실한 해결책은 lock의 순서를 모두 통일하는 것. 그래서 C++은 `std::lock`이라는 도구를 제공.

    ```cpp
    // worker 1, 2 내부에서 순서 상관없이 이렇게 쓰면 알아서 교착 상태를 피해 잠금.
    std::lock(mtxA, mtxB);

    // 해제도 안전하게 처리하기 위해 lock_guard와 조합.
    std::lock_guard<std::mutex> lockA(mtxA, std::adopt_lock);
    std::lock_guard<std::mutex> lockA(mtxB, std::adopt_lock);
    ```

  - `std::scoped_lock`
    위의 `std::lock_guard`를 따로 해줄 필요없이 함수가 끝날 때 알아서 해제를 해주는 방법. 알아서 해제해주기 때문에 가장 안전하고 가장 권장됨.

```cpp
void worker1(){
    // mtxA와 mtxB를 안전하게 동시에 잠금 (순서 꼬임 방지)
    std::scoped_lock lock(mtxA, mtxB);

    // do something...
} // 알아서 해제.
```
