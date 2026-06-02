#include <chrono>  // 시간을 다루기 위해 필요한 헤더
#include <iostream>
#include <thread>  // std::jthread를 쓰기 위해 필요한 헤더

int main() {
  std::cout << "메인 스레드 실행" << std::endl;

  // std::jthread 객체(jt)를 만들고, 람다식 함수에 stop_token을 인수로 주입.
  std::jthread jt([](std::stop_token token) {
    // 외부에서 멈추라는 신호(request_stop)를 보내기 전까지만 무한 루프를 돔.
    while (!token.stop_requested()) {
      std::cout << "스레드: 작업 중..." << std::endl;

      // 콘솔창이 너무 빨리 넘어가지 않도록 1초(1000밀리초)씩의 딜레이를 줌.
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // 루프를 빠져나왔다는 것은 안전하게 중단 신호를 처리했다는 뜻.
    std::cout << "스레드: 자원 정리 후 종료" << std::endl;
  });

  // 메인 스레드가 서브 일꾼(jt)을 띄워놓고 5초 대기.
  std::this_thread::sleep_for(std::chrono::seconds(5));

  std::cout << "메인 스레드 종료" << std::endl;

  // 메인 스레드가 서브 스레드에게 공식적으로 중단.
  jt.request_stop();
  // request_stop() 시 위의 token.stop_requested()가 true가 되어 while문 종료.

  std::cout << "메인 스레드, 메인 함수 종료" << std::endl;
  return 0;
  // 매우 중요: 여기서 jt 객체가 소멸하면서 내부적으로 jt.join()이 자동 호출!
}