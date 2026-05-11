#include <iomanip>  // io manipulators
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// 기본적으로 stream은 buffer 저장되어 있는 것을 임시적으로 꺼내오는 방식.
int main() {
  char buf[5];
  cin >> setw(5) >> buf;
  // 최대 5글자만 받도록 방지
  cout << buf << endl;
  cin >> setw(5) >> buf;
  cout << buf << endl;

  int a;
  float b;

  char c;

  while (cin >> c) cout << c;
  // cin으로부터 buffer를 가져올 때는 빈칸을 무시함
  // while로 하게 되면 키보드에 입력을 하고 enter를 누르면
  // cin은 버퍼에서 데이터를 꺼내 c에 넣고 true를 반환해 마우리 enter를 쳐도
  // 입력할 데이터를 기다리게 됨. 이때 cin에게 더 이상 들어올 데이터가 없다는
  // 것을 알려주기 위해 cntl + d를 눌러주는데 이게 바로 여기서의 EOF(End Of
  // File)

  while (cin >> a >> b) cout << a << " " << b << endl;
  // 스페이스로 구분해서 각각 a, b에 데이터를 넣음

  cin.get(buf, 5);
  cout << buf << endl;

  cin.get(buf, 5);
  cout << buf << endl;

  return 0;
}