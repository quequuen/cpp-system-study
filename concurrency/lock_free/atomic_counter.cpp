
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

constexpr int THREAD_COUNT = 4;
constexpr int ITERATIONS = 1'000'000;

std::atomic<int> counter{0};
// int와 비슷하게 정수 값을 저장하는 타입
// 여러 스레드가 동시에 접근하더라도 원자적인 연산을 제공
// atomic은 연산이 중간에 쪼개져 다른 스레드에 의해 간섭받지 않도록 보장하는
// 개념.

void increment() {
  for (int i = 0; i < ITERATIONS; ++i) {
    counter.fetch_add(1);
    // 현재 값에 1을 더하는 원자적 연산
    // 일반적인 counter++와 달리 여러 스레드가 동시에 호출해도 증가 연산이 서로
    // 유실되지 않음.
  }
}

int main() {
  std::vector<std::thread> threads;

  // 스레드 생성
  for (int i = 0; i < THREAD_COUNT; ++i) {
    threads.emplace_back(increment);
  }

  // 모든 스레드의 작업이 끝날 때까지 대기
  for (auto& thread : threads) {
    thread.join();
  }

  std::cout << "Counter: " << counter.load() << '\n';
  // atomic 변수에 저장된 현재 값을 읽는 연산
  std::cout << "Expected: " << THREAD_COUNT * ITERATIONS << '\n';

  std::cout << std::boolalpha << counter.is_lock_free() << '\n';
  // 현재 atomic 객체가 Lock-free 방식으로 동작하는지를 판단

  return 0;
}

// std::atomic을 사용했다고 해서 반드시 Lock-free 방식으로 구현되는 것이 아님.
// Atomic: 연산의 원자성을 보장하는 개념.
// Lock-free: 특정 스레드가 지연되더라도 시스템 전체적으로 적어도 하나의
// 스레드가 계속 진행할 수 있는 성질.