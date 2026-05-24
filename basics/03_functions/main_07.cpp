#include <iostream>
#include <tuple>

using namespace std;

// tuple<int, int> func() { return tuple<int, int>(180, 75); }
auto func() { return make_tuple(123, 456, 789, 10); }

int main() {
  //   tuple<int, int, int, int> result = func();
  //   cout << get<0>(result) << " " << get<1>(result) << endl;

  auto [a, b, c, d] = func();
  cout << a << " " << b << " " << c << endl;

  return 0;
}