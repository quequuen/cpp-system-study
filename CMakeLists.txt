cmake_minimum_required(VERSION 3.15)
project(cpp_system_study)

set(CMAKE_CXX_STANDARD 17)

# 실행 파일들이 build/bin에 생성되도록
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 각 학습 프로그램 추가
add_executable(basic_00 basics/00_basic-of-basics/main_00_basic_of_basics.cpp)
add_executable(variables_01 basics/01_variables/main_01_variables.cpp)
add_executable(io_stream_07 basics/07_io_streams/main_07_io.cpp)
add_executable(functions_03 basics/03_functions/main_03_func.cpp)
