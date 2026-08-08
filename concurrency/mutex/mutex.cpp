#include <iostream>
#include <mutex>
#include <thread>

int counter = 0;
std::mutex mtx;

void increase() {
  for (int i = 0; i < 100000; ++i) {
    mtx.lock();

    ++counter;

    mtx.unlock();
  }
  // 이렇게 되면 counter라는 공유 변수에 접근할 때 하나의 스레드만 접근할 수
  // 있음. 그렇다면 반복문마다 mtx로 락을 걸고 해제할 때 성능은 괜찮은가 →
  // 성능이 항상 괜찮을 수 없지만 그렇다고 넓은 범위로 잡아버리면

  mtx.lock();

  for (int i = 0; i < 100000; ++i) {
    ++counter;
  }

  mtx.unlock();

  // 이런 식으로 잡아버리면 t1이 작업을 할 때 아예 100000번을 기다렸다가 t2를
  // 동작시키게 됨. 스레드를 분리하는 의미가 사라짐. (동시성 X)
  // 때문에 mutex의 핵심은 "최소한으로 잡되 충분하게"
  // Critical Section은 가능한 한 짧게 유지를 해야 함.
}

int main() {
  std::thread t1(increase);
  std::thread t2(increase);

  t1.join();
  t2.join();

  std::cout << "counter = " << counter << '\n';
}