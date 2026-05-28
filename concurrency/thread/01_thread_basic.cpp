#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::timed_mutex mtx;

void smartWorker() {
  std::unique_lock<std::timed_mutex> lock(mtx, std::defer_lock);

  // 2초 동안만 자물쇠를 얻으려고 시도
  if (lock.try_lock_for(std::chrono::seconds(2))) {
    // 자물쇠 얻기 성공.
    std::cout << "이걸 주네" << std::endl;
  } else {
    // 2초 동안 기다렸는데 남이 안 열어줌 -> 교착 상태 예방을 위해 포기하고
    // 우회
    std::cout << "기다리다가 그냥 딴 거 하러 감ㅅㄱ" << std::endl;
  }
}

int main() {
  // 이렇게만 하면 자물쇠가 하나만 잠구는 거라서 데드락 안 걸림.
  // smartWorker();
  // 다른 스레드(나쁜 녀석)를 만들어서 자물쇠를 먼저 채워버림.
  std::thread badGuy([]() {
    mtx.lock();  // 자물쇠를 먼저 선점!
    std::this_thread::sleep_for(
        std::chrono::seconds(5));  // 5초 동안 절대 안 놔줌
    mtx.unlock();
  });

  // 잠시 0.1초만 쉬었다가 메인 스레드가 자물쇠를 뺏으러 가게 함.
  // (badGuy가 확실하게 먼저 lock을 걸 수 있도록 시간을 주는 것)
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // 메인 스레드가 자물쇠를 얻으러 들어감.
  smartWorker();

  badGuy.join();  // 서브 스레드 퇴근할 때까지 기다려주기

  // 전체 로직
  // 0초: badGuy 스레드가 태어나자마자 mtx 자물쇠를 잠그고 5초 동안 sleep
  // 0.1초: 메인 스레드가 smartWorker()로 진입해서 try_lock_for(2초) 호출
  // 2.1초까지: 메인 스레드가 badGuy에게 자물쇠를 달라고 2초 동안 기다리지만
  // badguy는 5초 동안 sleep이라 아직 안 깨어남. (= 줄 수 없음)
  // 2.1초(타임 아웃): 메인 스레드가 2초나 기다렸지만 주지 않아서 포기하고 else
  // 문으로 빠짐.

  return 0;
}