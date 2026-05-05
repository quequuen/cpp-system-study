#include <iomanip>  // io manipulators
#include <iostream>
#include <string>

using namespace std;

int main() {
  char buf[5];

  cin >> setw(5) >> buf;
  // 최대 5글자만 받도록 방지
  cout << buf << endl;
  cin >> setw(5) >> buf;
  cout << buf << endl;

  return 0;
}