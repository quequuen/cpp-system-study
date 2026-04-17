#include <iostream>
#include <list>
#include <algorithm>

int main() {
    std::list<int> l = {10, 20, 30};

    // 앞/뒤 삽입 (둘 다 빠름)
    l.push_front(5);
    l.push_back(40);

    // 중간 삽입
    auto it = l.begin();
    // it에 그 노드의 실제 주소(포인터 정보)와 더불어 앞뒤 노드를 찾을 수 있는 모든 정보 담음.
    ++it; // 한 칸 이동 (20을 가리킴)
    l.insert(it, 15); // 20 앞에 15 삽입

    // 순회 (it++ 만 가능, it+n은 안됨)
    for (int n : l) {
        std::cout << n << " ";
    }

    return 0;
}