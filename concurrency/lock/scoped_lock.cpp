#include <iostream>
#include <mutex>
#include <string>

class Account {
 private:
  std::string name;
  int balance;
  std::mutex mtx;

 public:
  Account(std::string name, int balance)
      : name(std::move(name)), balance(balance) {}

  // Bank가 mutex에 접근할 수 있도록
  std::mutex& getMutex() { return mtx; }

  const std::string& getName() const { return name; }

  int getBalance() const { return balance; }

  void withdraw(int amount) { balance -= amount; }

  void deposit(int amount) { balance += amount; }
};

class Bank {
 public:
  static void transfer(Account& from, Account& to, int amount) {
    // 두 계좌의 mutex를 안전하게 동시에 획득
    std::scoped_lock lock(from.getMutex(), to.getMutex());
    // 이체라는 하나의 작업은 withdraw와 deposit이라는 작업을 둘 다 완료 해야만
    // 함 그렇기 때문에 이체할 때는 둘 다 보호를 해야 함 각각의 mutex로 처리하는
    // 이유: 하나의 mutex로 전체를 잠그게 되면 규모가 커졌을 때 은행 전체가
    // 하나의 mutex로 묶여서 아무 관계 없는 계좌들도 서로의 작업이 끝날 때까지
    // 기다려야 함

    // 여기부터 Critical Section
    if (from.getBalance() < amount) {
      std::cout << "잔액 부족\n";
      return;
    }

    from.withdraw(amount);
    to.deposit(amount);

    std::cout << from.getName() << " -> " << to.getName() << " : " << amount
              << "원 이체\n";

  }  // 여기서 두 mutex 자동 unlock
};

int main() {
  Account alice("Alice", 100000);
  Account bob("Bob", 50000);

  std::cout << "이체 전\n";
  std::cout << "Alice: " << alice.getBalance() << "원\n";
  std::cout << "Bob: " << bob.getBalance() << "원\n\n";

  Bank::transfer(alice, bob, 30000);

  std::cout << "\n이체 후\n";
  std::cout << "Alice: " << alice.getBalance() << "원\n";
  std::cout << "Bob: " << bob.getBalance() << "원\n";

  return 0;
}