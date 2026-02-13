## 전체 구조

cpp-system-study/
├── README.md
├── CMakeLists.txt
├── .vscode/
│ ├── tasks.json
│ ├── launch.json
│ └── settings.json
├── basics/
│ ├── 01_variables/
│ ├── 02_control/
│ ├── 03_functions/
│ ├── 04_pointers/
│ ├── 05_references/
│ └── 06_arrays/
├── oop/
│ ├── 01_class/
│ ├── 02_inheritance/
│ ├── 03_polymorphism/
│ └── 04_virtual/
├── memory/
│ ├── new_delete/
│ ├── smart_pointers/
│ └── memory_pool/
├── stl/
│ ├── vector/
│ ├── map/
│ └── unordered_map/
├── concurrency/
│ ├── thread/
│ ├── mutex/
│ └── lock_free/
├── network/
│ ├── tcp/
│ ├── udp/
│ └── chat_server/
└── notes/
├── pointers.md
├── memory.md
└── concurrency.md

## 각 폴더 상세 구조

- basics (C++ 기초)

01_variables: 변수 선언, 데이터 타입(int, float, double, char), 상수, 초기화
02_control: 조건문(if, switch), 반복문(for, while, do-while), break, continue
03_functions: 함수 선언/정의, 매개변수, 반환값, 함수 오버로딩, 재귀함수
04_pointers: 포인터 기초, 주소 연산자(&), 역참조(\*), 포인터 연산
05_references: 참조자(&), 참조와 포인터 차이, 함수 매개변수로서의 참조
06_arrays: 배열 선언, 다차원 배열, 배열과 포인터 관계

- concurrency (동시성/병렬 프로그래밍)

lock_free: Lock-free 자료구조, atomic 연산, 무잠금 알고리즘
mutex: 뮤텍스(상호 배제), std::mutex, lock_guard, unique_lock
thread: 스레드 생성/관리, std::thread, join, detach, 동기화

- memory (메모리 관리)

memory_pool: 메모리 풀 구현, 메모리 할당 최적화
new_delete: new/delete 연산자, 동적 메모리 할당/해제
smart_pointers: unique_ptr, shared_ptr, weak_ptr, RAII 패턴

- network (네트워크 프로그래밍)

chat_server: 채팅 서버 구현 예제
tcp: TCP 소켓 프로그래밍, 클라이언트/서버 통신
udp: UDP 소켓 프로그래밍, 데이터그램 통신

- notes (학습 노트)

개인 메모, IDE 설정, 환경설정, 참고사항 등

- oop (객체지향 프로그래밍)

01_class: 클래스 기본, 멤버 변수/함수, 생성자/소멸자, 접근 제어
02_inheritance: 상속, protected, 다중 상속, 상속의 접근 제어
03_polymorphism: 다형성, 가상 함수, 순수 가상 함수, 추상 클래스
04_virtual: virtual 키워드, vtable, 가상 소멸자, override, final

- stl (Standard Template Library)

map: std::map, 정렬된 연관 컨테이너, key-value 쌍
unordered_map: std::unordered_map, 해시 테이블 기반 컨테이너
vector: std::vector, 동적 배열, capacity, push_back, iterator
