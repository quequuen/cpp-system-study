#include <chrono>
#include <iostream>
#include <mutex>

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
  smartWorker();

  return 0;
}