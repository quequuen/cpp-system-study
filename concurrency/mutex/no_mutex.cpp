#include <iostream>
#include <thread>

int counter = 0;

void increase() {
  for (int i = 0; i < 100000; ++i) {
    ++counter;
  }
}

int main() {
  std::thread t1(increase);
  std::thread t2(increase);

  t1.join();
  t2.join();

  std::cout << "counter = " << counter << '\n';
  // 레이스 컨디션의 기본 코드
  // 답이 200000이 아닌 106302가 나옴.
}