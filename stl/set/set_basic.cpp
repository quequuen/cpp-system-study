#include <iostream>
#include <set>

int main() {
    std::set<int> s;

    // 데이터 삽입
    s.insert(30);
    s.insert(10);
    s.insert(20);
    s.insert(10); // 중복: 무시

    // 순회 (10 20 30 순으로 자동 정렬되어 출력)
    for (int n : s) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // 값 찾기
    auto it = s.find(20);
    if (it != s.end()) { // end()는 실제 데이터가 들어있는 마지막 칸이 아닌, 가상의 빈칸을 가리키는 주소값.
        std::cout << "20이 집합에 존재합니다.\n";
    }

    // C++20 부터 가능
    // if (s.contains(20)){
    //     std::cout << "20이 집합에 존재합니다.\n";
    // }

    // 개수 확인
    if (s.count(10)) {
        std::cout << "10이 집합에 존재합니다.\n";
        // set은 자료가 중복되지 않기 때문에 count가 곧 존재/비존재가 될 수 있음.
    }

    return 0;
}