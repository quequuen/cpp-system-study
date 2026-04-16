#include <iostream>
#include <deque>

int main() {
    std::deque<int> dq;

    // 뒤에 추가
    dq.push_back(10);
    dq.push_back(20);

    // 앞에 추가 (vector에는 없는 기능!)
    dq.push_front(5);
    dq.push_front(1);

    // 순회: 1 5 10 20
    for (int n : dq) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // 인덱스 접근 가능
    std::cout << "두 번째 원소: " << dq[1] << "\n";

    return 0;
}