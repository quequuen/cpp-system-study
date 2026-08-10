## thread

### **프로세스 (Process)**

운영체제에서 메모리에 올라와 실행 중인 프로그램. 각 프로세스는 독립된 메모리 공간(코드, 데이터, 힙, 스택)을 갖고 운영체제로부터 필요한 자원(Resource, CPU 시간•메모리 주소 공간•파일•I/O 디바이스 등)을 할당받는 작업 단위.

- **독립된 메모리 구조**
  - **Code (Text)**: 컴파일된 소스 코드가 저장되는 영역 (Read-Only).
  - **Data**: 전역 변수(Global)와 정적 변수(Static)가 저장되는 영역.
  - **Heap**: 런타임에 동적으로 할당되는 메모리 영역(C++의 `new`, C의 `malloc` 등)
  - **Stack**: 함수 호출 시 생성되는 지역 변수와 매개 변수가 저장되는 영역 (함수 완료 시 소멸).
- **OS의 관리 단위**
  - **PCB (Process Control Block, 프로세스 제어 블록)**: 운영체제가 프로세스를 관리하기 위해 프로세스마다 생성하는 독자적인 정보 블록.
  - 프로세스 상태, PID(프로세스 ID), PC(Program Counter, 다음 실행할 명령어 주소), 레지스터 정보 등이 담겨 있음.
- **철저한 격리성**
  - 각 프로세스는 철저히 독립되어 있어 기본적으로 다른 프로세스의 메모리에 접근할 수 없음. (하나가 크래시 나도 다른 프로세스에 영향을 주지 않음)
  - 만약 프로세스 간에 데이터를 주고 받아야 한다면, OS가 제공하는 **IPC(Inter-Process Communication) 기법** (파이프, 소켓, 공유 메모리 등)을 사용해야 함.

### **스레드 (Thread)**

프로세스 안에서 실제로 작업을 수행하는 실행 흐름의 단위. 같은 프로세스 내의 스레드들은 메모리(자원)를 서로 공유하며 작동함. 2개 이상의 스레드가 프로세스 내부에 존재하는 것을 멀티 스레드 프로세스하고 함.

- 메모리 관점에서 본 스레드의 특징
  - 공유하는 영역: 데이터(Data) 영역, 힙(Heap) 영역.
    - 특징: 전역 변수나 동적 할당된 메모리는 모든 스레드가 다 같이 접근하고 수정할 수 있음. 주소록을 같이 쓰는 것과 같아서 서로 소통하기 편하지만, 동시에 수정하려 들면 데이터가 꼬이는 위험(`Data Race`)이 있음.
  - 독립적인 영역: 스택(Stack) 영역.
    - 특징: 스레드는 각자 자기만의 실행 대기열과 지역 변수를 가짐. 일반적으로 각 스레드가 자신의 스택을 가진다. 보통 경우에는 서로의 스택 영역을 건드리지 않음.
  - 메모리 외의 독립적인 영역: 레지스터(Register)와 PC(Program Counter)
    CPU 레지스터 상태와 PC(다음에 실행할 명령어의 메모리 주소를 가리키는 레지스터). 스레드가 교체되었다가 다시 돌아왔을 때 이전의 상태를 기억해야 하기 때문에 독립적인 영역으로 존재.

- 프로세스와 스레드의 비용 차이
  스레드는 프로세스보다 생성하고 전환(Context Switching)하는 비용이 압도적으로 저렴함. **새 프로세스를 만들려면 메모리 공간을 통째로 새로 파야 하지만, 스레드는 프로세스가 가진 방(Heap, Data)을 그냥 같이 쓰면서 몸만 들어가면 되기 때문.** (멀티 프로세스보다 멀티 스레드를 선호하는 이유)

### `std::thread`

OS의 실제 스레드를 제어하기 위한 C++의 클래스. 클래스라서 객체일 뿐임. 운영체제가 실제로 돌리는 스레드가 아님.

`std::thread t1(함수);`를 적으면 메모리에는 두 가지 공간이 생겨남.

- C++ object: 코드에서 제어할 수 있는 `t1`이라는 이름의 변수. 메인 스레드의 스택 영역에 생성.
- OS thread: 명령을 받자마다 CPU 코어 어딘가로 날아가서 실제로 일을 하기 시작하는 눈에 안 보이는 진짜 흐름임.

std::thread에 연관된 C++의 규칙: **스레드에게 작업을 시키고 있다면, 그 스레드와 연결된 객체(`t1`)가 메모리에서 사라지기 전에 반드시 관계를 정리(합류든 독립이든) 해야 함.**

- 합류/독립을 정리하는 메서드
  - `t1.join()`: 끝날 때까지 대기.
    메인 스레드가 `t1.join();`을 읽는 순간, CPU는 메인 스레드를 잠시 재우고 `t1` 스레드만 열심히 돌림. `t1`이 하던 일을 다 끝내고 `return`하거나 함수가 끝나면, 그제야 깨어난 메인 스레드가 `t1`이 쓰던 스택 메모리를 깨끗이 지워주고 다음 줄 코드로 넘어감.
  - `t1.detach()`: 독립.
    `t1.detach();`를 호출하면 `t1`이라는 객체와 실제 스레드 사이의 연결이 끊어짐. `t1`은 이제 관리하는 스레드가 없는 상태(Not Joinable)가 되어 메모리에서 사라지고, 실제 스레드는 백그라운드에서 혼자 무한 루프를 돌게 됨. 이때, 메인 스레드가 종료해야만 독립한 실제 스레드도 OS에 의해 강제로 증발함.
  - `t1.joinable()`: 프로그램이 죽는 것을 막아주는 안전장치 메서드. 반환 값으로 `true` 또는 `false`를 줌.
    이미 `join()`을 마쳤거나 `detach()`를 해버린 객체에 대고 한 번 더 `join()`을 호출하면 프로그램은 죽음. 그래서 안전하게 마무리 지을 때 필수로 사용.

    ```cpp
    if (t1.joinable())
    {
      t1.join();
    }
    ```

- 현재 작업 중인 스레드를 제어하는 메서드
  `t1.join()`처럼 객체에 명령을 내리는 것이 아닌 실제 작업 중인 스레드 스스로에게 명령을 내리는 특수한 메서드.
  - `std::this_thread::get_id()`
    - 현재 이 코드를 실행하는 스레드의 고유 ID를 출력.
  - `std::this_thread::sleep_for(시간)`
    - 작업 중인 스레드가 이 줄을 만나면 지정한 시간 동안 완전히 동작을 멈추고 수면 상태가 됨.
    - 너무 빠른 루프의 속도를 조절하거나, 동시성 타이밍을 강제로 꼬아서 테스트해 보고 싶을 때 애용.
  - `std::this_thread::sleep_until(시간_시점)`
    - 특정 시점(Absolute Time)을 지정해서 스레드를 재움.
    - `시간_지점`까지 수면 상태.
  - `std::this_thread::yield()`
    - 지금 CPU를 잡고 작업을 하던 스레드가 작업이 더 급한 스레드에게 운영체제 스케줄러에게 양보함.

- 하드웨어에 직접 관여하는 메서드
  - `std::thread::hardware_concurrency()`
    - 객체를 생성하는 것이 아닌 정적 메서드로 바로 접근.
    - 현재 내 컴퓨터의 CPU가 동시에 돌릴 수 있는 최대 스레드 개수를 알려줌. 4코어 8스레드라면 8을 출력.
    - 실제 스레드는 8인데 `std::thread` 객체를 더 많이 만든다면 스레드 교체(Context Switching) 비용 때문에 효율이 떨어짐. 실무에서는 이 함수가 뱉어준 개수만큼만 딱 스레드를 만들어서 효율적으로 사용하는 스레드 풀(Thread Pool) 기법을 사용.
  - `std::thread::hardware_destuctive_interference_size`
    - 현재 내 컴퓨터의 CPU의 L1 캐시 라인(Cache Line)의 크기를 바이트 단위로 출력.
    - 멀티스레딩에서 아주 심오한 성능 저하 원인 중 하나인 거짓 공유(False Sharing)을 막기 위해 사용. 서로 다른 두 스레드가 같은 캐시 라인에 묶여 있는 변수들을 동시에 수정하면 성능이 비약적으로 떨어짐. 이 함수는 알려주는 크기만큼 변수 사이의 간격을 벌려놓는(`alignas`) 하드웨어 최적화를 할 때 사용.

### `std::jthread` (Joinable thread)

`std::thread`의 매번 해주어야 하는 `join()` 처리를 알아서 자동으로 해주고, 중간에 안전장치까지 마련된 스레드 객체.

- 자동 합류(Auto-Join)
  `std::thread`는 `join()`이나 `detach()`를 깜빡하면 프로그램이 강제 종료됨. 하지만 `std::jthread`는 프로그램 종료 시 소멸자가 알아서 join()을 호출하고 안전하게 끝냄.

  ```cpp
  void test() {
      // std::thread는 함수가 끝날 때 t가 사라지면서 프로그램이 터짐.
      std::thread t([]() { /* 무한루프 */ });

      // std::jthread는 함수가 끝날 때 jt가 사라지면서 자동으로 jt.join()을 해줌.
      // 프로그램이 터지지 않고, 일꾼이 끝날 때까지 여기서 안전하게 기다려줌.
      std::jthread jt([]() { /* 작업 */ });
  }
  ```

- 협력적 중단(Cooperative Interruption)
  무한 루프를 돌고 있는 서브 스레드를 메인 스레드가 중간에 멈추게 하고 싶을 때, 기존에는 외부 변수를 조절하는 등 추가적인 코드가 필요했음. `std::jthread`는 중단 신호기(Stop Token)이라는 브레이크 장치를 내부에 기본 탑재함.

  ```cpp
  #include <iostream>
  #include <thread>
  #include <chrono>

  int main() {
      // 람다식 매개변수에 'std::stop_token'을 적어주면 컴파일러가 신호기를 꽂아줌.
      std::jthread jt([](std::stop_token token) {
          // 메인에서 멈추라고 하기 전까지만 돌기
          while (!token.stop_requested()) {
              std::cout << "스레드 작업 중...\n";
              std::this_thread::sleep_for(std::chrono::milliseconds(500));
          }
          std::cout << "스레드 종료 \n";
      });

      std::this_thread::sleep_for(std::chrono::seconds(2)); // 2초 대기

      // 메인 스레드가 그만하라고 명령함.
      jt.request_stop();

      return 0; // jt 소멸자가 자동으로 join()까지 호출.
  }
  ```

  - `stop_token`과 일반 커스텀 매개변수를 함께 전달하려면, 반드시 `stop_token`을 함수의 **첫 번째 매개변수**로 선언해야 함. 컴파일러가 첫 번째 인자로만 토큰을 주입하도록 설계되어 있기 때문.

| 특징             | `std::thread`                               | `std::jthread`                               |
| ---------------- | ------------------------------------------- | -------------------------------------------- |
| 소멸자 동작      | 마무리 처리가 없으면 **프로그램 강제 종료** | 내부에서 알아서 **자동 `join()` 호출**       |
| 중단 (취소) 가능 | 없음 (개발자가 수동으로 플래그 변수 구현)   | 내장된 **Stop Token**으로 안전하게 중단 가능 |
| 안전성           | 낮음                                        | 높음 (자원 누수와 크래시를 원천 차단)        |
| 사용 권장 버전   | C++11~17 프로젝트                           | C++20 이상 최신 프로젝트                     |

- **트러블슈팅: jthread를 썼는데 최종 값이 0이 나오는 이유**
  `std::jthread`가 자동으로 `join()`을 해주는 시점은 `main` 함수의 중괄호(`}`)가 완전히 닫히는 소멸 시점임. 따라서 그보다 위에 있는 `std::cout` 출력문은 서브 스레드들이 채 일을 시작하기도 전에 실행되므로 `0`이 찍히게 됨. 이를 해결하려면 출력문 전에 명시적으로 `t1.join()`을 호출해 순서를 보장해야 함. [트러블 슈팅 예시](../concurrency/thread/race_condition.cpp)

### **멀티 스레드 (Multi-thread)**

하나의 프로세스 안에 여러 개의 스레드를 만들어 여러 작업을 동시에 처리하는 방식.

- 장점: 여러 작업을 병렬로 처리하여 빠르게 처리할 수 있고 자원을 효율적으로 사용할 수 있음.
- 단점: 자원을 공유하기 때문에 하나의 스레드에 문제가 생기면 프로세스 전체에 영향을 줄 수 있음. 설계가 복잡함.
- 컨텍스트 스위칭 (Context Switching)
  CPU 코어는 한 번에 하나의 스레드만 처리할 수 있음. 그래서 스레드를 바꿀 때, 기존 하던 일의 상태를 저장하고 다음 상태를 불러오는 작업을 하는데 이를 컨텍스트 스위칭이라고 함. 하지만 이 작업이 너무 자주 일어나게 되면 컴퓨터가 쉽게 지침.(컨텍스트 스위칭 오버헤드)
  - 컨텍스트 스위칭 오버헤드 (Context Switching Overhead)
    CPU 코어 개수는 정해져 있는데 스레드만 너무 많으면, 작업은 안 하고 스레드 교체(컨텍스트 스위칭)하는 데만 CPU 자원을 다 써버려서 오히려 프로그램이 느려짐. 이를 **스래싱(Thrashing)** 현상이라고 부름.
    - 오버헤드(Overhead): 스레드가 바뀔 때 CPU 연산 자원이 낭비되는 '현상이나 비용' 그 자체를 뜻함.
    - 스래싱(Thrashing): 가상 메모리 영역에서 주로 쓰는 단어로, 메모리가 부족해 하드디스크와 메모리 사이에 페이지 교체(`Page Swap`)가 너무 자주 일어나서 컴퓨터가 마비되는 상태를 뜻함.
- 동기화 (Synchronization)
  여러 스레드가 공용 변수를 건드릴 때 순서를 정리해주는 기술.
- 비결정성 (Non-determinism)
  사실 스레드들의 실행 순서는 코딩한 순서대로 가지 않고, 운영체제(OS)의 스케줄러 마음대로 결정됨. 이 때문에 똑같은 코드를 돌려도 실행될 때마다 결과나 출력 순서가 바뀔 수 있어 디버깅이 매우 까다로움.
  - 비결정성의 이유: **선점형 스케줄링(Preemptive Scheduling)**
    - 주체: 운영체제(OS)의 스케줄러(Scheduler)
      컴퓨터의 한정된 자원(CPU 코어)을 효율적으로 활용하기 위해 운영체제가 코딩한 순서대로 가지 않는 것.
    1. 시분할(Time Sharing)과 선점(Preemption)
       코드로 스레드 3개(`t1`, `t2`, `t3`)를 만들어서 동시에 실행하라고 명령하면, CPU 코어 개수보다 스레드가 보통 훨씬 많기 때문에 스케줄러가 아주 짧은 시간 단위로 쪼개서 스레드에세 CPU를 번갈아 쥐여줌. 이걸 **시분할**이라고 함.
       이때 운영체제가 어떤 스레드가 CPU를 잡고 작업을 하고 있더라고 정해진 시간(Time Slice)이 지나면 **운영체제가 강제로 CPU를 뺏어서 다음 스레드에게 넘겨주는 게 선점형**이라는 규칙임.
    2. I/O 블로킹
       만약 스레드 A가 작업을 하다가 '네트워크에서 데이터 받아오기'나 '하드디스크에서 파일 읽기' 같은 작업(I/O 작업)을 만나면 컴퓨터 입장에서 CPU 연산 속도에 비해 인터넷이나 디스크의 속도는 굉장히 느림.
       그렇기 때문에 운영체제의 스케줄러가 판단해 스레드 A가 데이터를 기다리느라 대기 상태(`Blocked`) 경우, 그 시간동안 CPU를 스레드 B에게 줌.
    3. 스케줄러의 복잡한 알고리즘
       스케줄러는 단순히 차례대로 순찰을 도는 게 아니라, 컴퓨터 전체의 효율을 위해 아주 복잡한 계산을 함.
       - **우선순위(Priority)**: 지금 당장 화면을 그려야 하는 스레드나 마우스 입력을 받아야 하는 스레드에게 CPU를 우선적으로 밀어줌.
       - **기아 상태(Starvation) 방지**: 우선순위가 낮은 스레드가 너무 오랫동안 작업을 하지 못하고 있으면(`Starvation`), 스케줄러가 일시적으로 순서를 앞당겨주기도 함.

    결국 컴퓨터 내부의 상황(지금 실행 중인 다른 프로그램, 마우스 움직임, 네트워크 상태 등)이 매 순간 다르기 때문에, 스케줄러가 내리는 최적의 판단도 매번 달라짐. 그래서 똑같은 코드를 실행해도 실행할 때마다 스레드의 출력 순서가 뒤바뀌는 것.

### 레이스 컨디션 (Race Condition)

두 개 이상의 스레드가 하나의 공유 자원(전역 변수, 힙 메모리 등)을 동시에 수정하려고 서로 경쟁할 때, 스레드가 실행되는 타이밍이나 순서에 따라 결과 값이 매번 엉뚱하게 바뀌는 현상.

- 내부 메커니즘
  컴퓨터 하드웨어(CPU) 입장에서 메모리의 값을 더하는 연산은 한 번에 처리되지 않고 다음과 같이 3단계(Read → Modify → Write)로 쪼개져서 실행.
  - **Read**: 메모리에 있는 현재 공유 자원을 CPU 레지스터로 읽어옴.
  - **Modify**: 레지스터에 있는 값에 계산된 수행함.
  - **Write**: 계산된 값을 다시 원래 메모리에 덮어씀.

- 레이스 컨디션 시나리오
  1. `thread1`이 1단계(`Read`)를 실행해 공유 메모리를 읽어옴.
  2. 그 순간 OS 스케줄러가 `thread1`를 잠시 멈추고 `thread2`에게 CPU를 줌.
  3. `thread2`도 똑같이 1단계(`Read`)를 실행해 공유 메모리를 읽어옴.
  4. `thread2`가 2, 3단계를 쭉 실행해서 공유 메모리를 갱신.
  5. 다시 돌아온 `thread1`는 1단계에 2, 3단계를 실행 후 이전에 `thread2`가 전에 갱신해 놓은 공유 메모리를 또 갱신.

  결과적으로는 두 번의 작업이 이루어졌는데 `thread2`의 작업이 완전히 증발해 버린 것. → **데이터 유실(Lost Update)**

  ```cpp
  #include <iostream>
  #include <thread>
  #include <vector>

  // 모든 스레드가 동시에 접근할 공유 자원 (전역 변수)
  int counter = 0;

  void increaseCounter() {
    for (int i = 0; i < 100000; ++i) {
      // 이 한 줄이 내부적으로 Read -> Modify -> Write 로 쪼개지며
      // 레이스 컨디션이 발생
      counter++;
    }
  }

  int main() {
    // 두 개의 스레드를 동시에 가동
    {
      std::jthread t1(increaseCounter);
      std::jthread t2(increaseCounter);
    } // 여기서 두 스레드 종료 대기
    // jthread이므로 메인 함수 종료 시 자동으로 join() 되어
    // 두 스레드가 일을 마칠 때까지 기다려줌.

    // 최종 기대 값은 200000(20만)
    std::cout << "최종 Counter 값: " << counter << std::endl;

    return 0;
  }
  ```

- 해결 방법
  1. `std::mutex`와 `std::scoped_lock` 사용
  2. `std::atomic` 사용

### `Critical Section`

여러 스레드가 동시에 접근하면 문제가 발생할 수 있어서, 한 번에 하나의 스레드만 실행하도록 보호해야 하는 코드 영역. `mutex`와 서로 다른 개념이며 `mutex`는 **그 영역에 한 번에 하나만 들어가도록 하는 자물쇠**를 의미하고, `Critical Section`은 **보호해야 하는 코드 영역**을 의미함.
아래 `std::mutex` 예시

```
Thread 1 ── lock ──→ [ Critical Section ] ── unlock ──→
                         counter++

Thread 2 ── lock ──→        대기
                              ↓
                      Thread 1이 unlock
                              ↓
                     [ Critical Section ]
                         counter++
```

### `Lock`

`Critical Section`에 한 번에 하나의 스레드만 접근하도록 제한하는 동작.

```
Lock → [ Critical Section ] → Unlock
```

### `std::mutex`

`Race Condition`의 가장 범용적인 해결책. 공용 메모리를 한번에 딱 한 스레드만 들어올 수 있는 임계 구역(`Critical Section`)으로 만들고 자물쇠를 채워버리는 것.

```cpp
#include <iostream>
#include <thread>
#include <mutex> // 자물쇠를 쓰기 위해 헤더 추가

int counter = 0;
std::mutex mtx; // 공용 자물쇠 생성

void increaseCounter() {
    for (int i = 0; i < 100000; ++i) {
      std::scoped_lock lock(mtx);
        // C++20 표준에 맞춰 가장 안전한 scoped_lock을 채움.
        // 한 루프가 끝날 때 자동으로 자물쇠가 풀림.

      counter++;
    } // 여기서 자물쇠 해제 (unlock)
}

int main() {
    std::jthread t1(increaseCounter);
    std::jthread t2(increaseCounter);

    // jthread 소멸자가 알아서 join() 처리를 하므로 대기 코드는 생략
    return 0;
}
```

- 자물쇠를 잠그고 여는 행위(`Context Switching` 유발 및 대기 시간) 자체가 하드웨어 관점에서 꽤 무겁기 때문에 프로그램의 실행 속도가 자물쇠가 없을 때보다 눈에 띄게 느려짐. → `Lock`을 한다고 반드시 `Context Switching`이 발생하는 건 아님.
- 여러 스레드가 동시에 `Lock`을 요청해 경쟁이 발생하면, `Lock`을 획득하지 못한 스레드가 대기하면서 스케줄링 등의 비용이 발생할 수 있음. 따라서 `Critical Section`은 가능한 한 짧게 유지하는 것이 좋음.

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

    std::cout << "worker1 업무 완료!" << std::endl;
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

int main() {
    std::jthread t1(worker1);
    std::jthread t2(worker2);

    return 0;
  }
```

- 교착 상태는 한 마디로 잠그는 순서가 서로 달라서 발생. 그렇게 때문에 가장 쉽고 확실한 해결책은 lock의 순서를 모두 통일하는 것. 그래서 C++는 이러한 부분을 해소해주는 여러 객체를 제공.

### `RAII Lock`

직접 `lock()`/`unlock()` 하는 동작 자체는 위험할 수 있음. 그렇기 때문에 객체의 생성과 소멸을 이용해서 자동으로 관리하는 방식이 필요함. 이러한 방식을 지원하기 위해 `std::lock_guard`, `std::scoped_lock` 등의 객체가 생김.

- `std::lock`
  여러 개의 `mutex`를 동시에 안전하게 잠그기 위한 함수. `RAII Lock` 개념은 아니지만 비교용.

  ```cpp
  #include <iostream>
  #include <mutex>
  #include <thread>

  std::mutex mtxA;
  std::mutex mtxB;

  void worker() {
    // A와 B를 안전하게 동시에 lock
    std::lock(mtxA, mtxB);

    std::cout << "두 mutex를 모두 획득\n";

    // std::lock은 unlock까지 해주지는 않음
    // 직접 각각의 자물쇠를 unlock
    mtxA.unlock();
    mtxB.unlock();
  }

  int main() {
    std::jthread t1(worker);
    std::jthread t2(worker);

    return 0;
  }
  ```

- `std::lock_guard`
  `mutex`를 자동으로 잠그고 자동으로 풀어주는 RAII 객체.

### `std::atomic`

원자적. 공용 메모리의 3단계(Read → Modify → Write)를 쪼개지 않는 하나의 원자(Atomic) 연산으로 처리하라고 하는 것. 중간에 스케줄러가 끼어들 틈을 원천 차단.

```cpp
#include <iostream>
#include <thread>
#include <atomic> // 원자적 변수를 쓰기 위해 헤더 추가

// int 대신 std::atomic<int> 로 선언
std::atomic<int> counter = 0;

void increaseCounter() {
    for (int i = 0; i < 100000; ++i) {
        // atomic 변수는 ++ 연산이 하드웨어 수준에서 (Atomic) 처리
        counter++;
    }
}

int main() {
    std::jthread t1(increaseCounter);
    std::jthread t2(increaseCounter);

    return 0;
}
```

- 하드웨어 수준에서 두 개 변수를 동시에 원자적으로 다루는 건 불가능하기 때문에 값을 대입하고 싶다면 그 값 자체를 넘겨주어야 함.

```cpp
std::atomic<int> a = 10;
std::atomic<int> b = a; // 에러: 복사 생성자가 막혀있음.
```

- 소프트웨어적으로 스레드를 잠재우고 깨우는 자물쇠 방식이 아닌 CPU 하드웨어 기능(Lock 명령어)을 직접 쓰는 원자적 연산을 제공하므로, 단순한 공유 변수의 연산에는 `mutex`보다 효율적일 수 있음.

하지만 항상 `mutex`보다 빠른 것은 아니며, 복잡한 여러 공유 상태를 하나의 일관된 상태로 보호해야 한다면 `mutex`가 더 적합함.

- `std::mutex`: Mutual Exclusion(상호 배제)의 약자로, 여러 스레드가 공유 자원에 동시에 접근하지 못하도록 막는 동기화 도구.
- worker1이 A를 쥐고 B를 원함 → worker2이 B를 쥐고 A를 원함 → 프로그램은 이 지점에서 멈춰버리고 다음 코드로 넘어가지 못함. (deadlock 발생)
- 교착 상태가 성립하는 4가지 조건
  교착 상태는 다음 4가지 조건이 동시에 만족할 때만 발생. 역으로 말하면 이 중 하나라도 부수면 교착 상태를 예방할 수 있음.
  - **상호 배제 (Mutual Exclusion)**: 한 번에 한 스레드만 자원을 사용 가능.
  - **점유와 대기 (Hold and Wait)**: 자원 하나를 쥔 상태(`Hold`)에서 다른 자원을 달라고 기다림(`Wait`).
  - **비선점 (No preemption)**: 다른 스레드가 쥐고 있는 자원을 강제로 뺏어올 수 없음.
  - **순환 대기 (Circular Wait)**: 대기 관계가 원형 모양으로 꼬여있음 (A→B, B→A).

### 락 프리 프로그래밍(Lock-free Programming)

멀티스레딩 환경에서 최상급 성능과 안정성을 뒤어짜내기 위해 사용하는 고급 테크닉.
`std::mutex`같은 자물쇠(Lock)를 쓰지 않고 스레드들을 안전하게 돌리는 기법.

- 뮤텍스(`mutex`)나 `scoped_lock` 같은 자물쇠 기반 동기화는 구현하기 쉽지만, 치명적인 단점이 분명히 존재.
  - **스레드 차단 (Blocking)**: 자물쇠를 쥔 스레드가 작업을 마칠 때까지, 다른 스레드들은 CPU 자원을 반납하고 대기를 하고 슬립 상태에 들어감. 스레드가 잠들고 깨어나는 과정에서 **컨텍스트 스위칭 오버헤드**가 크게 발생함.
    - 뮤텍스 대기 시 하드웨어 및 OS 레벨의 실제 상태 변화
      1. 스레드 A가 CPU 코어에서 실행 중인 상태에서 뮤텍스를 잠금. (`lock`)
      2. 스레드 B가 똑같이 해당 뮤텍스의 `lock()` 함수를 호출함.
      3. 커널은 뮤텍스의 내부 상태(대개 원자적 카운트 값)를 확인하고, 이미 잠겨 있음을 인지하면 스레드 B를 즉시 실행 대기열에서 제외함.
      4. 이때 스레드 B의 TCB(Thread Control Block) 내의 상태값이 `RUNNING(실행)`에서 `BLOCKED(차단/대기)`로 전환.
      5. 운영체제 스케줄러는 스레드 B의 레지스터 세트(General Registers, SP, PC 등)를 현재 CPU 코어에서 백업하여 메모리에 저장함. 이를 컨텍스트 세이브(Context Save)라고 함.
      6. 스케줄러는 실행 가능한 다른 스레드의 컨텍스트를 해당 CPU 코어에 로드(`Context Resore`)하여 실행함.

    이 과정이 수행하는 동안 스레드 B는 CPU 연산 자원을 전혀 소모하지 않는 완전한 비활성화 상태(Sleep)가 됨. 이후 스레드 A가 `unlock()`을 호출하면 커널 인터럽트에 의해 스레드 B가 깨어나 `READY` 상태를 거쳐 다시 CPU 코어 할당을 받게 됨.

  - **데드락 (Deadlock)**: 순서가 꼬이면 프로그램이 영원히 멈춰버리는 교착 상태.
  - **우선순위 역전 (Priority Inversion)**: 중요하고 빠른 스레드가 일해야 하는데, 더 우선순위가 낮은 스레드가 자물쇠를 쥐고 놔주질 않아 시스템 전체가 먹통이 됨.

**락 프리(Lock-free)의 핵심 철학**: 시스템 안의 어떤 스레드가 멈추거나(Crash) 잠들더라도, 최소한 다른 한 개 이상의 스레드는 아무 방해 없이 계속 앞으로 나아가며 일을 처리할 수 있도록 보장한다.

- CAS(Compare-And-Swap, 비교 및 교환) 연산
  자물쇠도 없이 레이스 컨디션을 막을 수 있는 락 프리의 핵심 연산.
  - `std::atomic`의 `compare_exchange_strong()`
  - CAS는 CPU에게 3단계 과정을 **물리적으로 절대 쪼개지지 않는 하나의 원자적(Atomic) 행동**으로 처리하라고 명령.
    1. 현재 메모리에 있는 값이 예상한 값(Expected)랑 같은지 비교
    2. **똑같다면**: 다른 스레드가 접근하지 않았다고 판단 → CAS가 예상한 새로운 값(Desired)으로 바꿈. (성공: `true` 반환)
    3. **다르다면**: 다른 스레드가 먼저 와서 값을 바꿨다고 판단 → CAS가 예상한 값으로 바꾸지 않음. (실패: `false` 반환)

- 락 프리 프로그래밍은 자물쇠를 채우는 대신, 원하는 결과가 나올 때까지 무한 루프를 돌며 계속 Retry 하는 구조.

```cpp
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> counter = 0;

void lockFreeIncrease() {
    for (int i = 0; i < 100000; ++i) {
        // 현재 counter에 저장된 값을 일단 안전하게 읽어옴 (예상 값)
        int expected = counter.load();

        // 만들고 싶은 새로운 값
        int desired = expected + 1;

        // CAS 연산 (락 프리의 핵심 루프)
        // counter의 값이 내가 읽어왔던 expected와 여전히 똑같다면 desired로 교체
        // 만약 그새 다른 스레드가 가로채서 counter를 올려버렸다면,
        // 실패(false)하고 루프를 다시 돌며(Retry) 바뀐 counter 값을 새로 읽어와 재시도
        while (!counter.compare_exchange_strong(expected, desired)) {
            // 실패 시 expected는 현재 바뀐 최신 counter 값으로 자동 갱신
            desired = expected + 1;
        }
    }
}

int main() {
    std::jthread t1(lockFreeIncrease);
    std::jthread t2(lockFreeIncrease);

    t1.join();
    t2.join();

    std::cout << "락 프리 최종 값: " << counter.load() << std::endl; // 정확히 200000 출력
    return 0;
}
```

- 락 프리(`std::atomic`) 대기 시 하드웨어 및 OS 레벨의 실제 상태 변화
  1. 락 프리 알고리즘(예: CAS 루프)에서는 `std::mutex` 같은 커널 오브젝트나 시스템 콜을 호출하지 않음.
  2. 스레드는 코드가 컴파일된 CPU 명령어(예: x86의 `LOCK CMPXCHG`, ARM의 `LDREX/STREX`)를 루프 안에서 직접 실행.
  3. CAS 연산이 실패하면 코드는 `while` 조건문에 의해 다시 동일한 원자적 메모리 접근 명령어를 수행.
  4. 이 과정에서 스레드의 TCB 상태는 계속 `RUNNING(실행)` 상태를 유지함.

- 장점
  - **압도적인 속도와 전송량(Throughput)**: 스레드가 잠들고 깨어나는 오버헤드가 전혀 없기 때문에 초고속 연산 가능.
  - **데드락 불가능**: 자물쇠 자체가 없으므로 서로 물고 물리는 교착 상태가 원천적으로 발생하지 않음.
  - **안정성**: 하나의 스레드가 일을 하다가 크래시가 나거나 OS에 의해 멈추더라도, 다른 스레드들은 멈추지 않고 계속 작업을 함.

- 단점
  - **구현 난이도**: 락 프리로 연결 리스트(Linked List), 큐(Queue), 스택(Stack) 같은 복잡한 자료구조를 구현하기엔 너무 어려운 방식임.
  - **무한 재시도로 인한 CPU 낭비(Spinning)**: 경쟁이 너무 극심하면 스레드들이 계속 실해파면서 CPU 점유율만 100%를 치고 전체되는 현상이 생길 수 있음.

- **스레드의 대기 방식 차이**
  - **뮤텍스 (Sleep 방식)**: 자물쇠 획득 실패 기 스레드가 **대기(Blocked/Sleep) 상태**로 전환되어 CPU 자원을 반납함. 컨텍스트 스위칭 오버헤드가 발생하지만 CPU 점유율을 낭비하지 않음.
  - **락 프리 (Busy Waiting 방식)**: 실패해도 잠들지 않고 **실행(Running) 상태**를 유지하며 무한 루프를르 돌며 재시도함. 대기 시간이 짧을 때 극상의 성능을 내지만, 대기 시간이 길어지면 CPU 자원을 과도하게 소모함.

  - 기다리는 시간이 짧을 때는 오버헤드가 더 크기 때문에 락 프리가 빠르고, 기다리는 시간이 길 때는 무한 루프를 도는 락 프리보다 스레드를 재워두는 뮤텍스 방식이 좋음.

### `std::atomic`

뮤텍스(`std::mutex`) 같은 자물쇠(Lock)를 사용하지 않고도 **하드웨어(CPU) 레벨에서 여러 스레드가 동시에 안전하게 접근할 수 있도록 보장하는 원자적 변수 클래스.**

- 하드웨어 관점에서의 원자성(Atomicity)
  일반적인 자료형 변수의 연산은 C++ 코드로는 한 줄이지만 , CPU의 어셈블리 명령어 레벨에서는 **Read-Modify-Write**의 3단계 명령어로 쪼개져 실행.
  이 3단계 도중에 OS 스케줄러에 의해 컨텍스트 스위칭이 일어나면 데이터가 덮어써 지는 레이스 컨디션이 발생. 반면, `std::atomic`으로 선언하면 CPU는 이 3단계 과정을 더 이상 쪼개질 수 없는 하나의 단일 명령어(Atomic Instruction)로 처리함. CPU 아키텍처 레벨(x86의 `LOCK` 프리픽스, ARM의 `LL/SC` 등)에서 메모리 버스를 잠그거나 배타적 접근을 보장하므로, 연산 중간에 다른 스레드가 절대 개입할 수 없음.

- 연산자 오버로딩 지원
  정수형이나 bool형 변수에 대해 연산자가 오버로딩 되어 있어 일반 변수와 거의 동일한 문법으로 사용 가능.

- 복사 생성 및 복사 대입 불가
  다른 `std::atomic` 객체로의 복사나 대입이 금지되어 있음. 하드웨어적으로 두 개의 서로 다른 메모리 위치를 동시에 하나의 원자적 연산으로 처리할 수 없기 때문.

  ```cpp
  std::atomic<int> a = 10;
  std::atomic<int> b = a; // 컴파일 에러: 복사 생성자 미존재.

  b = a;                  // 컴파일 에러: 대입 연산자 미존재.
  ```

  값을 대입하고 싶다면 일반 `int` 값을 대입하거나, `store()`, `load()` 메서드를 사용.

- 핵심 메서드
  - `load()`와 `store()`
    원자적으로 값을 읽고 쓰는 명시적인 함수.
    - `load()`: 현재 변수에 저장된 값을 원자적으로 읽어옴.
    - `store(val)`: 변수에 새로운 값을 원자적으로 저장함.

    ```cpp
    std::atomic<bool> is_running = false;

    is_running.store(true); // 원자적 쓰기
    if (is_running.load()) { // 원자적 읽기
        // 실행 코드
    }
    ```

  - `exchange(val)`
    새로운 값으로 변경하는 동시에, 변경되기 직전의 원래 메모리에 있던 값을 한 번에(Atomic) 반환.

    ```cpp
    std::atomic<int> data = 100;
    int old_value = data.exchange(200);
    // 결과: data는 200이 되고, old_value에는 100이 저장됨
    ```

  - `compare_exchange_strong()` 및 `compare_exchange_weak()`
    멀티스레딩 고급 기법인 락 프리 알고리즘의 핵심 함수. 하드웨어의 CAS(Compare-And-Swap) 명령어 수행.
    **메모리의 현재 값이 내가 예상한 값(Expected)과 일치하면 새로운 값(Desired)으로 교체하고 `true`를 반환하며, 다르면 교체하지 않고 `false`를 반환한다.**

    ```cpp
    std::atomic<int> counter = 10;
    int expected = 10;
    int desired = 20;

    // counter가 expected(10)와 같으므로 desired(20)로 바뀌고 true 반환
    bool success = counter.compare_exchange_strong(expected, desired);
    ```

| 비교 항목       | `std::mutex`(자물쇠 방식)                                                           | `std::atomic`(원자적 방식)                                                     |
| --------------- | ----------------------------------------------------------------------------------- | ------------------------------------------------------------------------------ |
| 대기 메커니즘   | 자물쇠를 얻지 못하면 커널이 스레드를 `BLOCKED(Sleep)` 상태로 전환하고 CPU에서 내림. | 실패 시 스레드는 `RUNNING` 상태를 유지하며 루프를 돌며 재시도하서나 즉시 실행. |
| 비용 (오버헤드) | 컨텍스트 스위칭 비용이 발생함.                                                      | 컨텍스트 스위칭 비용이 전혀 없음 (하드웨어 명령어 속도).                       |
| 보호 범위       | 복잡한 객체, 여러 줄의 코드, 함수 전체를 임계 구역으로 묶어 보호 가능.              | 단일 기본 자료형(`int`, `bool`, `pointer` 등) 크기의 메모리에만 적용 가능.     |

### 비동기 프로그래밍

작업이 완료될 때까지 기다리지 않고 다음 코드를 실행하는 방식. 파일 읽기나 네트워크 요청 등 응답 대기 시간이 긴 작업이 있을 때 동기 방식을 사용하면 프로그램 전체가 멈추는(Blocking) 현상이 발생함. 비동기는 이 대기 시간 동안 다른 작업을 수행할 수 있게 해줌.

```cpp
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

// 커피 만드는 작업
string makeCoffee() {
  cout << "커피 제조 시작...\n";

  this_thread::sleep_for(chrono::seconds(3));

  cout << "커피 완성!\n";
  return "아메리카노";
}

// 빵 굽는 작업
string bakeBread() {
  cout << "빵 굽기 시작...\n";

  this_thread::sleep_for(chrono::seconds(5));

  cout << "빵 완성!\n";
  return "크루아상";
}

int main() {
  cout << "카페에 입장했습니다.\n\n";

  // 비동기 작업 시작

  // 나중에 string을 받을 예정인 객체
  // 3초가 지나면  결과값을 받음.
  future<string> coffeeFuture = async(launch::async, makeCoffee);
  // async 함수가 이 함수를 별도의 비동기 작업으로 실행하라는 명령을 함.
  // 실제로는 메인 스레드 외 새로운 스레드를 할당받아 실행됨.
  future<string> breadFuture = async(launch::async, bakeBread);

  cout << "음료를 기다리는 동안 결제합니다.\n";

  this_thread::sleep_for(chrono::seconds(1));

  cout << "결제 완료!\n\n";

  // 결과가 아직 없으면 기다리는 작업
  // 이미 끝났다면 즉시 반환
  string coffee = coffeeFuture.get();
  string bread = breadFuture.get();

  cout << "\n===== 주문 완료 =====\n";
  cout << coffee << endl;
  cout << bread << endl;
}
```

### `std::future`

그저 '결과를 저장하는 변수'가 아닌 **미래에 값이 준비될 것이라는 약속을 관리하는 객체**. `std::future<T>`는 T타입의 값을 담는 객체가 아니라, 나중에 T 타입의 결과가 준비되면 받아올 수 있는 '권리'를 나타내는 객체.

위 코드에서 async 내부에서는

```
(main thread →) async() → 새로운 thread 생성 → makeCoffee() 실행 → 결과(string) 생성 → shared state에 저장 ← future가 바라봄
```

이런 동작을 하게 됨. 여기서 중요한 것은 **shared state**.

- **Shared state**
  future는 사실 값을 직접 들고 있는 것이 아님.

  ```
  future
    ↓
  shared state
    ├── 결과가 준비됐는가?
    ├── 결과 값
    ├── 예외가 발생했는가?
    ├── 작업이 끝났는가?
    └── 대기 중인 스레드가 있는가?
  ```

  위의 구조로 공유 메모리 공간을 가리킴. 그래서 처음에는 Shared state에 아무 값이 없는 상태였다가 몇 초 뒤 값이 생기는 것을 future가 가리키는 것.

### Shared state

**공유 메모리 + 상태 정보.** 값만을 저장하는 공간이 아닌 비동기 작업 전체를 관리하는 객체. `std::async`를 하면 `std::future`가 값을 갖는 것이 아닌 이 `shared state` 내부에 값을 저장함. `std::future`는 그저 이 `shared state`를 가리키는 핸들(handle).

```cpp
template<typename T>
struct SharedState {

    T value;              // 결과값

    bool ready;           // 준비됐는가

    std::exception_ptr e; // 예외 발생 여부

    std::mutex m;         // 동기화

    std::condition_variable cv;

};
```

### `future::get()`

`std::future<T>::get()`. 다양한 일을 하지만 기본적으로 **Shared State에 저장된 결과를 가져오는 멤버 함수.**

```cpp
int work() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 100;
}

auto future = std::async(work);

int result = future.get();
// 이 과정에서 ready == false를 비교하고 false라면 현재 스레드를 Block 상태로 만듦.
```

- 즉, `future.get()`은 **결과가 준비될 때까지 현재 스레드를 멈춤.** `get()`이 완료되면 `Shared State`와 `future`와의 연결을 끊음. 그래서 해당 작업 이후 `future.get()`을 다시 하게 되면 예외가 발생함. `get()`이 한 번만 가능한 이유는 `future`가 '결과를 받을 권리'를 나타내기 때문.
- `get()`은 `future`의 템플릿 타입(<T>)을 그대로 반환.

### `future::wait()`

`std::future<T>::wait()`. **Shared State의 결과가 준비될 때까지 현재 스레드를 대기시키는 멤버 함수.** 값을 가져오지 않고 기다리기만 한다는 점이 `get()`과의 차이점.

- 기본 구조

```cpp
void future<T>::wait() {
    // 실제 구현이 아닌 개념적인 동작
    while (!state->ready) {
        // 결과가 준비될 때까지 대기
    }
}
```

실제로는 `busy waiting`('바쁜 대기', 반복문으로 Shared State의 상태를 계속 확인하는 방식)을 하지 않고 `condition_variable`(스레드를 잠재운 뒤 조건이 만족되면 깨우는 동기화 객체) 등을 사용해서 효율적으로 대기함.

```cpp
int work() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 100;
}

auto future = std::async(work);
// 이 상태인 경우, auto가 std::future<int> 타입으로 추론됨.
// future 객체는 Shared State를 참조함.

future.wait();
// wait()을 호출하게 될 경우
// Shared State가 sleep_for로 인해 아직 work()가 종료되지 않았으므로 value: ?, readey: false 상태.
// 그러므로 현재 스레드는 대기(Block) 상태가 됨.
// 작업이 완료된 순간 Shared State의 상태는 value: 100, ready: true가 됨.
// ready가 true가 되면 wait()이 반환. 하지만 여전히 future는 Shared State를 참조함. get과는 다르게 연결이 해제되지 않음.
// get과는 다르게 결과를 소비(consume)하지 않기 때문.

std::cout << "작업 완료\n";

int value = future.get();
// get()이 결과를 반환한 후 future와 Shared State의 연결이 해제된다.
```

- 결과를 바로 사용할 거라면 `get()`.
- 결과는 아직 필요 없고 작업이 끝났는지만 확인하고 싶은 경우 `wait()`.
- 위 코드에서는 `future.wait()`이 동기화(Synchronization) 역할을 함.
- `wait()`

  ```cpp
  future.wait();
  ```

  결과가 준비될 때까지 무한히 기다림.

- `wait_for()`

  ```cpp
  while (future.wait_for(std::chrono::milliseconds(100))
       != std::future_status::ready)
  {
    std::cout << "아직 작업 중...\n";
  }
  ```

  일정 시간 기다림. 일정 시간 안에 끝나면 바로 `ready`를 반환하고, 끝나지 않으면 `timeout` 시간 초과 상태를 반환. 위처럼 사용하게 되면 `0.1초 기다림` → `안 끝남` → `"아직 작업 중..."` → `다시 0.1초 기다림` → `안 끝남` → `"아직 작업 중..."`을 반복.

- `wait_until()`

  ```cpp
  future.wait_until(deadline);
  ```

  특정 시간까지 기다림.

### `std::promise`

**Shared State에 결과(또는 예외)를 저장하는 객체**이다. 비동기 작업의 결과를 전달하는 객체. 결과를 받아오는 객체 `future`와는 반대.

```cpp
Producer                  Consumer

promise   ─────────────►   future
   │                          ▲
   │                          │
   ▼                          │
  Shared State────────────────┘
```

- `promise` → 값을 저장.
- `future` → 값을 추출.

```cpp
#include <future>
#include <iostream>

int main() {

    std::promise<int> promise;  // promise 생성

    std::future<int> future = promise.get_future();   // future 생성
    // 여기서 둘은 같은 Shared State를 보게 됨.

    promise.set_value(100);   // 값 저장

    std::cout << future.get();    // 값 추출

}
```

- `get_future()`: Shared State를 공유하는 future를 만듦.
- `set_value()`: Shared State에 값을 넣고 `ready = ture`가 됨.

```cpp
#include <future>
#include <thread>
#include <iostream>

void work(std::promise<int> promise)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));

    promise.set_value(777);
}

int main()
{
    std::promise<int> promise;

    auto future = promise.get_future();

    std::thread t(work, std::move(promise));

    std::cout << "Waiting...\n";

    std::cout << future.get();

    t.join();
}
```

- `std::promise`는 **복사가 금지(copy deleted)** 되어 있기 때문에 `std::move`를 사용해 소유권을 이전. 복사를 허용하게 되면 어떤 promise가 Shared State에 값을 넣어야 하는지 불분명해짐.
  - [Move Semantics](./smart_pointers.md#무브시맨틱)

→ `async`는 이 promise/future 과정을 라이브러리가 자동으로 처리해 주는 **고수준 인터페이스**. 구현은 표준 라이브러리마다 다를 수 있지만, 동작 구조는 promise/future 모델과 매우 유사함.

### `std::packaged_task`

호출 가능한 객체(함수, 람다 등)를 감싸고, 실행 결과를 Shared State에 저장하는 객체. 쉽게 `함수 + Promise`라고 이해하면 됨.

```cpp
#include <future>
#include <iostream>

int work() {
    return 100;
}

int main() {

    std::packaged_task<int()> task(work);
    // 생성과 동시에 work() 함수를 task 객체 안에 넣음.
    // 생성자가 work 함수를 task 객체 안에 저장.

    auto future = task.get_future();
    // future와 연결.

    task();
    // 함수 호출 연산자 operator()를 호출해 작업 실행.

    std::cout << future.get();
}
```

- `set_value()`라는 메소드를 사용해 Shared State에 값을 저장하는 `promise`와는 다르게 자동으로 Shared State에 값을 저장.

- 개념적 구조

  ```cpp
  class packaged_task {

      int (*func)();

  public:

      packaged_task(int(*f)()) {
          func = f;
      }

      void operator()() {
          int result = func();

          // Shared State 저장
      }
  };
  ```

  - 바로 thread를 생성하는 `async`와는 다르게 thread를 생성하지 않고 메인 스레드에서 작업함. 작업 자체를 저장해 작업을 즉시 실행하지 않고, 원하는 시점에 실행할 수 있음.

### `std::async`

스레드를 직접 손으로 만들고 관리하지 않고, 특정 함수를 비동기(백그라운드)로 실행시킨 뒤 그 '결과 값'을 나중에 받아오기 위해 사용하는 표준 함수. `future`를 만들어 주는 함수라고 생각하면 됨. 기존 `std::thread`는 반환 값 (`return`)을 직접 돌려줄 수 없어서 전역 변수나 매개변수 포인터/참조를 써야 했습니다. 하지만 `std::async`는 작업의 반환 값을 간편하게 받아올 수 있음. 내부 구현은 완전히 같지는 않지만, `std::thread` + `std::package_task`로 이해하면 됨.

- 함수 원형

```cpp
template<class F, class... Args>
std::future<ReturnType>
async(F&& f, Args&&... args);
```

→ `std::async`는 원래부터 `future`를 반환하는 함수. 그렇기 때문에 보통 `auto f = std::async(work);`로 작성해도 컴파일 시 auto가 `std::future`로 치환됨.

```cpp
auto future = std::async(work);
```

↓

```cpp
// 1. shared state 생성
SharedState<int>* state = new SharedState<int>();

// 2. 새로운 스레드 시작
thread([state] {
    int value = work();
    state->value = value;
    state->ready = true;
});

// 3. shared state를 가리키는 future 반환
// 실제 값은 shared state 내에 저장.
return std::future<int>(state);
```

따라서 async의 반환값은 '값'이 아닌 **'값을 기다리는 객체'**.

- `Launch Policy`(실행 정책)
  `std::async`가 비동기 작업을 어떤 방식으로 실행할지를 결정하는 정책.
  `std::async(...)`를 호출했을 때 새로운 스레드 생성 여부, 즉시 실행 여부를 결정.
  - `std::launch::async`: 즉시 새로운 스레드를 만들어 작업을 실행.
  - `std::launch::deferred`: 작업을 즉시 실행하지 않고, `future.get()` 또는 `future.wait()`가 호출될 때 현재 스레드에서 실행.

    ```cpp
    int work()
    {
        std::cout << "Work\n";
        return 100;
    }

    int main()
    {
        auto future =
            std::async(std::launch::deferred, work);

        std::cout << "Main\n";

        future.get();
        // 이때 work() 실행.
    }
    ```

    ```
    Main
    Work
    ```

    - `wait()`도 `deferred`라면 작업을 실행시켜서 보통 `wait_for()`를 사용함.
