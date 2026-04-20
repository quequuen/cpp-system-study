## STL (Standard Template Library)

C++에서 가장 강력하고 핵심적인 표준 템플릿 라이브러리. 크게 4가지 구성 요소로 나뉨.

- **컨테이너 (Containers)**: 데이터를 담는 그릇.
  데이터를 어떤 구조로 저장할지 결정.
  - 시퀀스 컨테이너: 순서가 있는 데이터 (vector, list deque)
  - 연관 컨테이너: 키(Key)를 바탕으로 데이터를 저장 (set, map)
  - 비정렬 연관 컨테이너: 해시 테이블 기반 (unordered_map, unordered_set)

- **반복자 (Iterators)**: 컨테이너를 가리키는 포인터.
  컨테이너의 종류와 상관없이 내부의 원소들을 순회할 수 있게 해주는 포인터.
  - 포인터와 비슷하게 `*`(역참조)나 `++`(다음 원소) 연산자를 사용.
  - 모든 컨테이너는 `begin()` (첫 번째 원소)과 `end()` (마지막 원소 다음)라는 반복자를 제공.

- **알고리즘 (Algorithms)**: 데이터를 처리하는 기능.
  정렬, 검색, 복사 등 데이터를 다루는 함수 모음. 특정 컨테이너에 종속되지 않고 반복자를 통해 작동함.
  - `std::sort()`: 데이터 정렬
  - `std::find()`: 특정 값 찾기
  - `std::copy()`: 데이터 복사

- **함수 객체 (Functors) / 람다 (Lambdas)**: 동작을 규정.
  알고리즘이 동작할 때 기준을 정해줌.

### STL 컨테이너 선택 가이드 (Decision Tree)

1. **데이터가 순차적으로 쌓는가?**
   - 중간 삽입/삭제 없이 끝에만 쌓음 → `std::vector`
   - 데이터 크기가 고정되어 있음 → `std::array`
2. **중간에 삽입/삭제가 빈번한가?**
   - 앞뒤 양쪽에서 삽입/삭제가 일어남 → `std::deque`
   - 데이터가 아주 많고 중간에 넣고 빼는 게 핵심 → `std::list`
3. **키(Key)를 가지고 데이터를 찾는가?**
   - 데이터가 정렬되어 있어야 함 → `std::map`(Red-Black Tree 기반)
   - 정렬 필요 없고 속도(검색)가 제일 중요함 → `std::unordered_map`(Hash Table 기반)

- 컨테이너별 시간 복잡도($Big-O$) 비교 테이블
  | 컨테이너 | 랜덤 접근 (`v[i]`) | 끝부분 삽입/삭제 | 중간 삽입/삭제 | 검색 |
  | -------- | ------------------ | ---------------- | -------------- | ---- |
  | `vector` | $O(1)$ | $O(1)$(Amortized) | $O(N)$ | $O(N)$ |
  | `deque` | $O(1)$ | $O(1)$ | $O(N)$ | $O(N)$ |
  | `list` | $O(N)$ | $O(1)$ | $O(N)$ | $O(N)$ |
  | `map` | 불가능 | $O(\log N)$ | $O(\log N)$ | $O(\log N)$ |
  |`unordered_map` | 불가능 | $O(1)$ | $O(1)$ | $O(1)$ |

### `std::vector`

크기가 자유롭게 변하는 동적 배열. 일반 배열은 처음에 정한 크기를 바꿀 수 없지만, vector는 데이터가 늘어나면 스스로 메모리를 확장함. 최근에는 90% 이상의 상황에서 `vector`를 쓰며 `list`는 중간 삽입이 빠르다고 배우지만 현대 CPU의 캐시 효율(Cache Locality) 때문에 메모리가 나란히 붙어 있는 `vector`가 실제로는 더 빠른 경우가 많음.

- `vector`의 특징
  - **연속된 메모리**: 데이터가 메모리상에 나란히 붙어 있음. 덕분에 인덱스(v[i])를 통한 접근이 매우 빠름.
  - **동적 확장**: 공간이 부족하면 더 큰 메모리 공간을 새로 할당받아 기존 데이터를 이사시킴.
  - **끝단 작업 최적화**: 맨 뒤에 데이터를 넣거나(push_back) 빼는(pop_back) 작업은 매우 빠르지만, 중간에 삽입/삭제하는 것은 데이터를 밀고 당겨야 해서 느림.
  - **단점**
    - 중간 삽입/삭제가 $$O(N)$$으로 느림.
    - 재할당(Reallocation) 발생 시 오버헤드 있음.

- Capacity(용량) vs Size(크기)
  - Size: 현재 실제로 들어있는 데이터의 개수.
  - Capacity: 새로운 할당 없이 담을 수 있는 최대 공간.

  만약 Size가 Capacity를 초과하려고 하면, `vector`는 보통 기존 용량의 1.5~2배의 새로운 공간을 찾아 전체를 이사시킴(Reallocation, 비용 높음).

```cpp
#include <iostream>
#include <vector>

int main() {

    // 선언 및 초기화
    std::vector<int> v = {10, 20, 30};
    // capacity 생성
    v.reserve(100);

    // 데이터 추가
    // 객체를 만들어서 복사하거나 이동
    // v.push_back(40);
    // v.push_back(50);

    // vector가 관리하는 메모리 안에서 객체를 바로 생성(불필요한 복사 방지)
    v.emplace_back(40);
    v.emplace_back(50);

    // 데이터 접근
    std::cout << "첫 번째 요소: " << v[0] << "\n";
    std::cout << "세 번째 요소: " << v.at(2) << "\n"; // at()은 범위를 체크해서 더 안전함

    // 반복문을 이용한 순회
    for (int n : v) {
        std::cout << n << " ";
    }

    // 크기 확인
    std::cout << "\n크기: " << v.size() << ", 용량: " << v.capacity() << "\n";

    return 0;
}
```

- 들어오는 데이터의 크기를 미리 알 수 있는 경우, `reserve()`를 사용하여 미리 공간을 예약한다면 Reallocation 횟수를 줄여 성을을 획기적으로 높일 수 있음. 현대에서는 `reserve`는 선택이 아닌 필수임.
- `push_back()`은 객체를 만들어서 복사하거나 이동시키지만 `emplace_back()`은 `vector`가 관리하는 메모리 안에서 객체를 바로 생성하기 때문에 불필요한 복사를 방지함.
- `clear()`로 용량은 유지하면서 모든 원소를 제거할 수 있음.

참고: [arrays.md#vector](arrays.md#stdvector)

### `std::deque`

Double-Ended Queue의 약자. 양쪽 끝에서 삽입과 삭제가 모두 가능한 선형 컨테이너. `vector`와 `list` 사이에서 유용한 절충안으로 사용됨.

- 내부 구조 (Chunk 방식)

  `vector`는 하나의 커다란 연속된 메모리 덩어리를 사용하지만, `deque`는 **여러 개의 작은 메모리 블록(Chunk)**을 할당하고 이를 관리하는 **인덱스 테이블(Map)**을 가짐.
  - 구조: `deque`의 반복자는 단순히 주소 하나만 들고 있는 게 아니라, 보통 4개 정도의 정보를 들고 다님.
    - 현재 가리키는 원소의 주소
    - 현재 속헤 있는 청크의 시작 주소
    - 현재 속해 있는 청크의 끝 주소
    - 중앙 테이블(Map)에서 몇 번째 청크인지에 대한 정보
  - 동작 방식(`it++`)
    1. 현재 청크의 끝에 도달했는지 확인.
    2. 아직 끝이 아니라면 옆 주소로 이동.
    3. 끝일 경우, 중앙 테이블을 보고 다음 청크의 시작 주소로 점프.

- `vector` vs `deque`

| 특징           | `std::vector`              | `std::deque`                    |
| -------------- | -------------------------- | ------------------------------- |
| 메모리 형태    | 단일 연속 메모리           | 분산된 블록 (Chunk)들           |
| 앞쪽 삽입/삭제 | 매우 느림 ($O(N)$)         | 매우 빠름 ($O(1)$)              |
| 뒤쪽 삽입/삭제 | 매우 빠름 ($O(1)$)         | 매우 빠름 ($O(1)$)              |
| 원소 접근      | 매우 빠름 (완전 연속)      | 약간 느림 (블록 확인 절차 필요) |
| 메모리 재할당  | 전체 복사 발생 (비용 높음) | 새 블록만 할당 (비용 낮음)      |

- 양방향에 최적화 되어 있으며 메모리가 부족할 때 통메모리를 찾지 않아고 되므로 대용량 데이터에도 유리함.
- 중간 삽입/삭제 같은 경우 `vector`와 동일하게 데이터를 밀고 당겨야 하므로 느림. ($O(N)$)
- 메모리가 물리적으로 완전히 이어져 있지 않아서 반복자(Iterator) 연산이 `vector`보다 복잡하고 미세하게 느림.
- 주로 큐를 구현하거나 데이터를 앞뒤로 넣어야 하거나 메모리 재할당(이사) 비용이 걱정될 때 사용.

```cpp
#include <iostream>
#include <deque>

int main() {
    std::deque<int> dq;

    // 뒤에 추가
    dq.push_back(10);
    dq.push_back(20);

    // 앞에 추가 (vector에는 없는 기능)
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
```

### `std::list`

**이중 연결 리스트(Doubly Linked List)**라는 자료구조로 구현됨. `vector`처럼 메모리가 다닥다닥 붙어 있는 것이 아닌, 데이터들이 메모리 여기저기에 흩어져 있고 서로 앞뒤 주소 정보로 연결된 형태.

- **중간 삽입/삭제가 빠름($O(1)$)**: `vector`는 중간에 하나를 넣으려면 뒤의 데이터를 다 밀어야 함. `list`는 옆 노드와의 포인터 연결만 새로 하면 됨.
- **임의 접근([] 접근) 불가($O(N)$)**: 중간에 있는 데이터를 보려면 첫 번째 노드부터 순서대로 물어보며 찾아가야 함.
- **메모리 오버헤드**: 데이터 하나를 저장할 때마다 앞뒤 노드의 주소값(포인터 2개)를 추가로 저장해야 하므로 메모리를 더 많이 씀.

- `vector` vs `list`

| 특징           | `std::vector`        | `std::list`                  |
| -------------- | -------------------- | ---------------------------- |
| 메모리 구조    | 연속됨(배열)         | 흩어짐(노드)                 |
| 조회 (`v[i]`)  | 매우 빠름 ($O(1)$)   | 느림 ($O(N)$)                |
| 중간 삽입/삭제 | 느림(밀어야 함)      | 매우 빠름 ($O(1)$)           |
| 반복자(it)     | `it + 5` (점프 가능) | `++it` (한 칸씩만 이동 가능) |

```cpp
#include <iostream>
#include <list>
#include <algorithm>

int main() {
    std::list<int> l = {10, 20, 30};

    // 앞/뒤 삽입 (둘 다 빠름)
    l.push_front(5);
    l.push_back(40);

    // 중간 삽입 (밀기 없음)
    auto it = l.begin();
    // it에 그 노드의 실제 주소(포인터 정보)와 더불어 앞뒤 노드를 찾을 수 있는 모든 정보 담음.
    ++it; // 한 칸 이동 (20을 가리킴)
    l.insert(it, 15); // 20 앞에 15 삽입

    // 순회 (it++ 만 가능, it+n은 안됨)
    for (int n : l) {
        std::cout << n << " ";
    }
    // 출력: 5 10 15 20 30 40

    return 0;
}
```

- `l.sort()`: `std::sort()` 사용 금지. 리스트는 전용 정렬 함수를 써야 함.
- `l.unique()`: 인접한 중복 원소를 제거함.
- `l.splice()`: 다른 리스트의 요소를 툭 떼어서 내 리스트에 추가. (데이터 복사 없이 연결만 바꿈)
- `l.begin()`: 단순한 숫자가 아니라, 내부적으로 첫 번째 노드의 메모리 주소값을 반환.

### `std::map`

키(Key)와 값(Value)을 한 쌍으로 묶어서 관리하는 자료형.

- Key(키): 데이터를 찾기 위한 고유한 식별자
- Value(값): 키에 연결된 실제 데이터

- 내부 구조: 균형 이진 트리 (Red-Black Tree)
  map은 내부적으로 노드들이 트리(Tree) 구조로 연결되어 있음.
  - 자동 정렬: 데이터를 넣기만 하면 키(Key)를 기준으로 알아서 오름차순 정렬.
  - 검색 속도: 처음부터 끝까지 다 찾는 게 아니라, 트리 줄기를 타고 내려가기 때문에 데이터가 100만 개 있어도 약 20번의 비교($O(\log N)$)면 원하는 데이터를 찾음.

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    // 선언: <키 타입, 값 타입>
    std::map<std::string, int> inventory;

    // 데이터 추가
    inventory["Sword"] = 1;
    inventory.insert({"Shield", 5});

    // 데이터 찾기
    std::cout << "Sword 개수: " << inventory["Sword"] << "\n";

    // 반복자로 순회
    // it->first는 Key, it->second는 Value를 의미함
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        std::cout << "아이템: " << it->first << ", 수량: " << it->second << "\n";
    }

    return 0;
}
```

- **중복 키 불가**: 똑같은 키로 값을 넣으면 기존 데이터가 덮어씌워짐. (중복이 필요할 경우 `multimap` 사용)
- `[]` **연산자 주의점**: `operator[key]`이라고 조회를 할 시 키가 존재하지 않는 경우에, `map`은 기본값으로 해당 키에 대한 데이터를 새로 생성해 버리기 때문에 데이터가 있는지 확인만 할 때에는 `find()` 함수를 쓰는 것이 안전함.
- **반복자 이동**: `it++`를 하면 트리 구조를 타고 정렬된 다음 순서의 노드로 이동함.

### `std::pair`

`map`은 데이터를 저장할 때 Key와 Value를 하나로 묶어야 함. 이때 C++ 표준 라이브러리가 사용하는 도구가 바로 `std::pair`

- 내부 구조

```cpp
template <typename T1, typename T2>
struct pair {
    T1 first;
    T2 second;
};
```

- `map`에 데이터 하나를 넣는다는 건, 내부적으로 `pair<Key, Value>` 타입의 노드를 하나 만드는 것과 같음.
- 첫 번째 멤버의 이름이 first, 두 번째 멤버의 이름이 second이기 때문에 `map`에서 반복자로 순회할 때 각각 `it->first`, `it->second`로 순회함.

### `std::unordered_map`

`std::map`이 **정렬된 사전**이라면 `std::unordered_map`은 **정렬없는 빠른 보관함**. 정렬이 꼭 필요한 게 아닐 경우 `std::map` 대신 `std::unordered_map`을 사용하는 게 성능 면에서 압도적으로 좋음.

- 내부 구조: Hash Table 구조. 해시 함수에 키 값을 넣으면 해당하는 값을 저장한 주소를 알려주기 때문에 빠름. ($O(1)$)
- `map`은 도서관의 책, `ordered_map`은 개인 사물함 느낌.
- <unordered_map> 헤더 파일 사용.

```cpp
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
```

- **해시 충돌 (Collision)**: 아주 가끔씩 서로 다른 키가 해시 함수를 통과할 때, 같은 주소의 데이터가 나올 때가 있음. `unordered_map`은 이럴 때 해당 칸에 데이터를 연결(Separate Chaining)해서 보관하기 때문에 충돌이 너무 많아지면 속도가 $O(N)$까지 느려질 수 있음. 하지만 이 부분도 C++ 라이브러리가 관리.
- 속도를 단축하기 위해 메모리를 `map`보다 더 많이 씀. 해시 충돌을 줄이기 위해 넉넉하게 빈 메모리(bucket, 버킷)들을 점유해 놓기 때문.
- **로드 팩터(Load Factor) 관리**: 버킷이 꽉 찰 경우(75% 이상) 검색 속도가 느려지기 때문에, 더 큰 배열을 새로 만들어서 통째로 이사함. (Rehash)
