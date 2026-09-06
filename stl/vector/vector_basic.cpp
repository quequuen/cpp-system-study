#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {10, 20, 30};
    v.reserve(100);

    // 객체를 만들어서 복사하거나 이동
    // v.push_back(40);
    // v.push_back(50);

    // vector가 관리하는 메모리 안에서 객체를 바로 생성(불필요한 복사 방지)
    v.emplace_back(40);
    v.emplace_back(50);

    std::cout << "첫 번째 요소: " << v[0] << "\n";
    std::cout << "세 번째 요소: " << v.at(2) << "\n"; // at()은 범위를 체크해서 더 안전함

    for (int n : v) {
        std::cout << n << " ";
    }

    std::cout << "\n크기: " << v.size() << ", 용량: " << v.capacity() << "\n";

    return 0;
}