cmake_minimum_required(VERSION 3.15)
project(cpp_system_study)

set(CMAKE_CXX_STANDARD 17)

# 실행 파일들이 build/bin에 생성되도록
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 각 학습 프로그램 추가
add_executable(basic_01 basics/00_basic-of-basics/main_00_basic_of_basics.cpp)
add_executable(basic_02 basics/00_basic-of-basics/main_00_basic_of_basics_02.cpp)
add_executable(basic_03 basics/00_basic-of-basics/main_00_basic_of_basics_03.cpp)
add_executable(variables_01 basics/01_variables/main_01_variables.cpp)
add_executable(variables_02 basics/01_variables/main_01_variables_02.cpp)
add_executable(variables_03 basics/01_variables/main_01_variables_03.cpp)
add_executable(variables_04 basics/01_variables/main_01_variables_04.cpp)
add_executable(variables_05 basics/01_variables/main_01_variables_05.cpp)
add_executable(variables_06 basics/01_variables/main_01_variables_06.cpp)
add_executable(variables_07 basics/01_variables/main_01_variables_07.cpp)
add_executable(variables_08 basics/01_variables/main_01_variables_08.cpp)
add_executable(control_01 basics/02_control/main_02_control.cpp)
add_executable(control_02 basics/02_control/main_02_control_02.cpp)
add_executable(control_03 basics/02_control/main_02_control_03.cpp)
add_executable(pointers_01 basics/04_pointers/main_04_pointers.cpp)
add_executable(io_stream_07 basics/07_io_streams/main_07_io.cpp)
add_executable(functions_03 
    basics/03_functions/main_03_func.cpp
    basics/03_functions/utils.cpp
)
