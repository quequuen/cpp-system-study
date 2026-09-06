# C++ System Study

C++ 시스템 프로그래밍 개인 스터디 저장소입니다.
기초 문법부터 OOP, 메모리 관리, STL, 동시성, 네트워크 프로그래밍까지
주제별 예제 코드와 학습 노트를 함께 정리합니다.

## 학습 목표

- C++ 언어의 핵심 및 고급 기능 이해 (C++20 기준)
- 객체지향 프로그래밍과 다형성/가상 함수 동작 원리
- 동적 메모리 관리와 스마트 포인터, RAII
- STL 컨테이너와 반복자
- 멀티스레딩 및 동시성 프로그래밍
- 소켓 기반 네트워크 프로그래밍 (TCP/UDP)

## 디렉터리 구조

```
cpp-system-study/
├── basics/         C++ 기초 (변수, 제어문, 함수, 포인터, 배열, IO, 템플릿, 예외, 파일)
├── oop/            객체지향 (클래스, 상속, 다형성, 가상 함수)
├── memory/         메모리 관리 (new/delete, 스마트 포인터, 메모리 풀)
├── stl/            STL (vector/deque/list, set, map, unordered_map, iterator)
├── concurrency/    동시성 (thread, mutex, lock, lock-free)
├── network/        네트워크 (tcp, udp, chat_server)
├── notes/          주제별 학습 노트 (Markdown)
├── CMakeLists.txt  빌드 대상 정의
└── vcpkg.json      의존성 매니페스트
```

각 폴더의 상세 구성은 [folder-structure.md](folder-structure.md)를 참고하세요.

## 요구사항

- C++20 지원 컴파일러 (Clang, GCC, MSVC)
- CMake 3.20 이상
- [vcpkg](https://github.com/microsoft/vcpkg) — 의존성 관리 (매니페스트 모드)

### 의존성

`vcpkg.json` / `CMakeLists.txt`에 정의된 라이브러리는 CMake 설정 시 vcpkg가 자동으로 설치합니다.

- [fmt](https://github.com/fmtlib/fmt) — 포매팅 라이브러리
- [Boost](https://www.boost.org/) — `network/tcp` 예제에서 사용

## 빌드 및 실행

vcpkg 툴체인 파일을 지정해 CMake를 설정합니다. (`$VCPKG_ROOT`는 vcpkg 설치 경로)

```bash
cmake -B build -S . \
  -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake

# 전체 빌드
cmake --build build

# 특정 대상만 빌드
cmake --build build --target thread_01
```

실행 파일은 `build/bin/`에 생성됩니다.

```bash
./build/bin/thread_01
```

빌드 대상 이름은 `CMakeLists.txt`의 `add_executable(...)` 항목에서 확인할 수 있습니다.

### 단일 파일 컴파일

CMake 없이 개별 예제만 빠르게 확인할 때:

```bash
clang++ -std=c++20 -o program basics/01_variables/main_01_variables.cpp
./program
```
