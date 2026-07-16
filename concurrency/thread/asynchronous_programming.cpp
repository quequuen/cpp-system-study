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