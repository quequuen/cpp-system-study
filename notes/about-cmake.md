## About CMake

CMake는 크로스 플랫폼 빌드 시스템, 소프트웨어 프로젝트의 빌드 과정을 자동화하는 도구. 소스 코드 파일을 컴파일하고 링크하여 실행 파일이나 라이브러리를 생성하는 데 필요한 설정을 관리.

### 주요 개념

- **CMakeLists.txt**: CMake 프로젝트의 핵심 구성 파일. 이 파일에는 빌드할 소스 파일, 포함할 라이브러리, 컴파일 옵션 등이 정의.
- **CMake 명령어**: CMakeLists.txt 파일에서 사용되는 다양한 명령어들 존재. 예를 들어, `add_executable()`는 실행 파일을 생성하는 데 사용되고, `target_link_libraries()`는 특정 타겟에 라이브러리를 링크하는 데 사용.
- **빌드 디렉토리**: CMake는 소스 코드와 별도의 빌드 디렉토리를 생성하여 빌드 아티팩트를 관리합니다. 이는 소스 코드와 빌드 결과물을 분리하여 관리하기 쉽게 합니다.
  +) - dsym : 디버그 심볼(debug symbol) 파일 축약어.

### CMake 사용 과정

1. **CMakeLists.txt 작성**: 프로젝트의 루트 디렉토리에 CMakeLists.txt 파일을 생성하고, 필요한 설정과 명령어를 작성.
2. **빌드 디렉토리 생성**: 소스 코드와 별도의 디렉토리를 만들어 빌드 아티팩트를 관리.
3. **CMake 실행**: 터미널에서 `cmake` 명령어를 사용하여 빌드 디렉토리에서 CMakeLists.txt 파일을 처리.
4. **빌드 실행**: `make` 또는 `cmake --build .` 명령어를 사용하여 실제 빌드를 수행.
5. **실행 파일 실행**: 빌드가 완료되면 생성된 실행 파일을 실행. (ex: `./bin/your_executable`)

### 주의사항

- 폴더 구조를 수정하거나 파일을 이동할 경우, CMakeLists.txt 파일 내의 경로도 함께 수정해야 함.
- 빌드 디렉토리를 삭제하고 다시 생성하는 것이 때때로 필요할 수 있음.
- CMakeLists.txt 파일에 실행 파일을 만들라고 등록은 했는데, 정작 main 함수가 들어있는 소스 파일을 리스트에 포함하지 않을 때(혹은 main.cpp 내 main 함수가 누락되거나 오타가 났을 때) Undefined symbos for architecture arm64: "\_main", referenced from: <initial-undefines> 에러 발생.

# `CMakeLists.txt` 작성법

- `cmake_minimum_required()`: 최소 버전 정의.
- `project()`: 프로젝트 이름 정의.
- `set (CMAKE_CXX_STANDARD 20/CMAKE_CXX_STANDARD_REQUIRED ON/CMAKE_CXX_EXTENSIONS OFF)`: C++ 버전 정의.
- `add_executable()`: 실행 파일 생성.
- `target_include_directories()`: 특정 target이 헤더 파일을 찾을 경로 지정.
- `target_link_libraries()`: 특정 target이 사용할 라이브러리를 연결.
- `find_package()`: 외부 라이브러리의 CMake 설정을 찾아서 사용 가능하게 함.

# 일반적인 C++ 프로젝트 `CMakeLists.txt` 작성법

- 폴더 구조

```
server/
├── CMakeLists.txt
├── vcpkg.json
├── include/
│   ├── server.h
│   └── database.h
└── src/
    ├── main.cpp
    ├── server.cpp
    └── database.cpp
```

- CMakeLists.txt

```
cmake_minimum_required(VERSION 3.20)

project(my_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fmt CONFIG REQUIRED)

add_executable(my_server
    src/main.cpp
    src/server.cpp
    src/database.cpp
)

# 헤더 파일 추가
target_include_directories(my_server
    PRIVATE
    include
)

# 외부 라이브러리 추가
target_link_libraries(my_server
    PRIVATE
    fmt::fmt
)
```

- vcpkg.json (외부 라이브러리 패키지 설정 파일)

```
{
    "name": "my-server",
    "version-string": "0.1.0",
    "dependencies": [
        "fmt"
    ]
}
```

→ 하지만 이 프로젝트는 학습용이기 때문에 각각의 파일을 따로 빌드함.
