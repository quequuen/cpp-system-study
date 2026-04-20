#include <iostream>
#include <unordered_map> 
#include <string>

int main() {
    std::unordered_map<std::string, int> scores;

    // 데이터 삽입
    scores["Gemini"] = 100;
    scores["User"] = 95;
    scores["Alpha"] = 80;

    // 출력 시 순서 상관없이 나옴.
    for (const auto& pair : scores) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    if (scores.find("Gemini") != scores.end()) {
        std::cout << "찾았다!\n";
    }

    return 0;
}