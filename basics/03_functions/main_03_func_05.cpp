#include <iostream>
#include <cassert>
#include <array>

void printIndexValue(const std::array<int, 5> &my_arr, const int& idx)
{

    assert(idx >= 0);
    assert(idx <= my_arr.size()-1);
    std::cout << my_arr[idx] << std::endl;
}

int main()
{

    std:: array<int, 5> my_arr{1, 2, 3, 4, 5};

    printIndexValue(my_arr, 3);

    const int a = 2;

    // 런타임 시 에러 발생
    assert(a == 10); 

    // 컴파일 시 에러 발생(좀 더 안전)
    // static_assert(a == 10, "a is 10");
    

    return 0;
}