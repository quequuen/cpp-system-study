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
  mtxA.unlock();
  mtxB.unlock();
}

int main() {
  std::jthread t1(worker);
  std::jthread t2(worker);

  return 0;
}