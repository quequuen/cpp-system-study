#include <fstream>
#include <iostream>

// binary로 파일 저장하는 법

struct Player {
  int id;
  double health;
  char level;
};

int main() {
  Player p1 = {1, 95.5, 'A'};

  // 바이너리 모드로 파일 열기
  std::ofstream ofs("player.dat", std::ios::binary);

  if (!ofs) return 1;

  // 데이터 쓰기
  // write(데이터의 주소, 데이터의 크기)
  // 이때 주소는 반드시 (char*)로 형변환(Casting)해야 함.
  // Player 객체는 덩어리가 크기 때문에 이걸 char*(1바이트 단위 주소)로 강제로
  // 변환해서 전달하면, 함수가 그 주소부터 sizeof(p1)만큼의 바이트를 순서대로
  // 파일에 복사하게 됨.
  ofs.write(reinterpret_cast<const char*>(&p1), sizeof(p1));

  ofs.close();

  Player p2;

  // 바이너리 모드로 파일 읽기
  std::ifstream ifs("player.dat", std::ios::binary);

  if (!ifs) return 1;

  // 데이터 읽기
  // read(데이터를 담을 주소, 읽어올 크기)
  ifs.read(reinterpret_cast<char*>(&p2), sizeof(p2));

  std::cout << "ID: " << p2.id << ", Health: " << p2.health
            << ", Level: " << p2.level << std::endl;
  return 0;
}