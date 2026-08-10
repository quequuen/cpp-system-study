#include <iostream>
#include <mutex>
#include <thread>

int counter = 0;
std::mutex mtx;

void increaseCounter() {
  for (int i = 0; i < 100000; ++i) {
    std::lock_guard<std::mutex> lock(mtx);
    // mutex의 소멸을 관리해주는 RAII 객체
    // 주로 하나의 mutex를 관리
    counter++;
  }
}

int main() {
  {
    std::jthread t1(increaseCounter);
    std::jthread t2(increaseCounter);
  }

  std::cout << counter << std::endl;

  return 0;
}