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
  // 두 명의 일꾼을 동시에 가동
  std::jthread t1(increaseCounter);
  std::jthread t2(increaseCounter);

  // jthread이므로 메인 함수 종료 시 자동으로 join() 되어
  // 두 스레드가 일을 마칠 때까지 기다려줌.

  // 최종 기대 값은 200000(20만)
  std::cout << "최종 Counter 값: " << counter << std::endl;
  // 근데 값이 매번 바뀜.
  // 이게 바로 레이스 컨디션.

  return 0;
}