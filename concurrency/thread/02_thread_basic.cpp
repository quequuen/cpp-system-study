#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

int main() {
  std::cout << std::thread::hardware_concurrency() << std::endl;
  // 몇 개의 코어를 가진 CPU에서 구동을 할 건지 확인 할 수 있음.

  std::thread t1 = std::thread([]() {
    std::cout << std::this_thread::get_id() << std::endl;
    while (true) {
    }
  });

  // 오류 발생: 10
  // libc++ abi : terminating[1] 49863 abort bin / thread_02 return 0;
  // 메인 스레드와 관계없는 t1 스레드가 생겨나 어떠한 처리와 상호작용을 하기
  // 전에 메인 스레드 종료

  t1.join();
  // 이러면 오류 발생하지 않음.
  // 하지만 강종 시키지 않으면 cpu 내 계속 구동. 활성상태에서 확인 가능.
}