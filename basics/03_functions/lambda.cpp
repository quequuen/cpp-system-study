#include <algorithm>   // count_if, for_each 사용
#include <functional>  // std::function (람다 저장용) 사용
#include <iostream>
#include <sstream>
#include <string>  // 문자열 처리
#include <vector>  // 데이터 저장용

using namespace std;

struct Student {
  string name;
  int score;
};

int main() {
  vector<Student> students = {{"옷코츠 유타", 85},
                              {"판다", 45},
                              {"젠인 마키", 92},
                              {"이누마키 토게", 30}};

  int passScore = 60;

  // 점수가 기준치 이상인지 확인하는 람다
  function<bool(int)> isPassed = [passScore](int s) -> bool {
    return s >= passScore;
  };

  // count_if와 람다 사용
  int passedCount =
      count_if(students.begin(), students.end(), [&](const Student& s) {
        return isPassed(s.score);  // 위에서 만든 람다를 안에서 호출
      });

  cout << "합격자 수: " << passedCount << "명" << endl;
  cout << "--- 합격자 명단 (이름 변경) ---" << endl;

  // for_each와 람다를 사용해 데이터 가공 및 출력
  for_each(students.begin(), students.end(), [isPassed](const Student& s) {
    if (isPassed(s.score)) {
      // 람다 안에서 즉석으로 이름을 꾸며서 출력
      auto decorator = [](string name) { return "[" + name + " - PASS]"; };
      cout << decorator(s.name) << " 점수: " << s.score << endl;
    }
  });

  return 0;
}