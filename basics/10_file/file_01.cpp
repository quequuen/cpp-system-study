#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  // writing
  // ofstream: output file stream
  // std::ios의 자식 클래스임.
  std::ofstream ofs("hello.dat");  // ios.app, ios::binary
  // ofs.open("hello.dat");
  // 생성자를 이용해 열 수도, open() 메소드를 이용해 열 수도 있다.
  // build 아래에 해당 이름의 파일 생성됨.

  // 파일이 존재 하지 않는다면 출력 하고 종료
  if (!ofs) {
    std::cerr << "Couldn't open file!" << std::endl;
    exit(1);
  }

  ofs << "안녕 내 이름은" << std::endl;
  ofs << "한가연" << std::endl;

  // ofs.close();
  // close() 메소드로 닫을 수 있지만 해당 스코프를 벗어나면 자동으로 소멸자가
  // 닫음.
  std::ifstream ifs("hello.dat");

  // read
  if (!ifs) {
    std::cerr << "Couldn't open file!" << std::endl;
    exit(1);
  }

  while (ifs) {
    std::string str;
    getline(ifs, str);

    std::cout << str << std::endl;
  }
  return 0;
}