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
add_executable(variables_09 basics/01_variables/main_01_variables_09.cpp)

add_executable(control_01 basics/02_control/main_02_control.cpp)
add_executable(control_02 basics/02_control/main_02_control_02.cpp)
add_executable(control_03 basics/02_control/main_02_control_03.cpp)
add_executable(control_04 basics/02_control/main_02_control_04.cpp)
add_executable(control_05 basics/02_control/main_02_control_05.cpp)

add_executable(pointers_01 basics/04_pointers/main_04_pointers.cpp)
add_executable(pointers_02 basics/04_pointers/main_04_pointers_02.cpp)
add_executable(pointers_03 basics/04_pointers/main_04_pointers_03.cpp)
add_executable(pointers_04 basics/04_pointers/main_04_pointers_04.cpp)
add_executable(pointers_05 basics/04_pointers/main_04_pointers_05.cpp)
add_executable(pointers_06 basics/04_pointers/main_04_pointers_06.cpp)

add_executable(arrays_01 basics/06_arrays/main_06_arrays.cpp)
add_executable(arrays_02 basics/06_arrays/main_06_arrays_02.cpp)
add_executable(arrays_03 basics/06_arrays/main_06_arrays_03.cpp)
add_executable(arrays_04 basics/06_arrays/main_06_arrays_04.cpp)
add_executable(arrays_05 basics/06_arrays/main_06_arrays_05.cpp)
add_executable(arrays_06 basics/06_arrays/main_06_arrays_06.cpp)

add_executable(io_stream_07 basics/07_io_streams/main_07_io.cpp)

add_executable(functions_01 
    basics/03_functions/main_03_func.cpp
    basics/03_functions/utils.cpp
)
add_executable(functions_02 basics/03_functions/main_03_func_02.cpp)

