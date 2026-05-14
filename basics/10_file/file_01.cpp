#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  // writing
  // ofstream: output file stream
  // std::ios의 자식 클래스임.
  std::ofstream ofs("hello.dat");
  // std::ios::app(append 모드), std::ios::binary(binary 저장), std::ios::ate
  // (파일을 열자마자 포인터를 끝으로 보냄), std::ios::trunc(파일을 열 때 기존
  // 내용을 모두 지움. 기본값임) ofs.open("hello.dat"); 생성자를 이용해 열 수도,
  // open() 메소드를 이용해 열 수도 있다. build 아래에 해당 이름의 파일 생성됨.

  // 파일이 없거나 권한 문제, 경로 문제 등으로 안 열렸을 때 체크
  if (!ofs.is_open()) {
    std::cerr << "Couldn't open file!" << std::endl;
    // exit(1);
    return 1;
    // C++ main 함수에서는 이 방법이 좀 더 권장됨.
    // 객체들의 소멸자가 더 안전하게 호출됨.
  }

  ofs << "안녕 내 이름은" << std::endl;
  ofs << "한가연" << std::endl;
  // 파일에 쓰는 양이 많을 경우, endl;보다 \n이 더 빠름. endl;은 줄바꿈과 동시에
  // 버퍼를 강제로 비우는(flush) 작업을 수행함.

  // ofs.close();
  // close() 메소드로 닫을 수 있지만 해당 스코프를 벗어나면 자동으로 소멸자가
  // 닫음.
  std::ifstream ifs("hello.dat");

  // read
  if (!ifs.is_open()) {
    std::cerr << "Couldn't open file!" << std::endl;
    return 1;
  }
  std::string str;

  //   while (ifs) {
  //     getline(ifs, str);

  //     std::cout << str << std::endl;
  //   }
  // 마지막 줄을 읽고 난 뒤 한 번 더 실행되어 빈 줄이 출력됨.

  while (getline(ifs, str)) {
    std::cout << str << std::endl;
  }
  return 0;
}