#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  cout.setf(std::ios::uppercase);
  // 아래 출력될 d를 대문자로 변경함.

  cout.setf(std::ios::hex, std::ios::basefield);
  // std::ios는 c++ 입출력 스트림 시스템에서 가장 뿌리가 되는 조상 클래스.
  // 위는 16진수로 설정하는 코드.
  cout << 109 << endl;

  cout << std::dec;
  cout << 2020 << endl;

  cout << true << " " << false << endl;
  cout << std::boolalpha;
  cout << true << " " << false;

  // cout << std::defaultfloat << endl;
  // 총 자릿수
  cout << std::fixed << endl;
  // 소수점 자릿수
  cout << std::setprecision(2) << 123.4567 << endl;
  cout << std::setprecision(3) << 123.4567 << endl;
  cout << std::setprecision(4) << 123.4567 << endl;
  cout << std::setprecision(5) << 123.4567 << endl;
  cout << std::setprecision(6) << 123.4567 << endl;
  cout << std::setprecision(7) << 123.4567 << endl;
  cout << std::setprecision(8) << 123.4567 << endl;

  cout << -1234567 << endl;
  cout.fill('*');
  // 공백을 '*'로 채워줌
  cout << std::setw(10) << -1234567 << endl;
  cout << std::setw(10) << std::left << -1234567 << endl;
  cout << std::setw(10) << std::right << -1234567 << endl;
  cout << std::setw(10) << std::internal << -1234567 << endl;

  return 0;
}