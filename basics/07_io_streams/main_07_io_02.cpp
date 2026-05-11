#include <iostream>

using namespace std;

int main() {
  // cout.setf(std::hex);
  // cout << 108 << endl;

  cout.unsetf(std::ios::showpos);
  cout << 109 << endl;
  return 0;
}