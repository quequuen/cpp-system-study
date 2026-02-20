#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

void printArray(const array<int,5> & arr)
{
    for (auto &el : arr)
    {
        cout << el << " ";
    }
    cout << endl;

}

int main()

{
    // std::array<타입, 크기> 이름;
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    // 실질적으로는 array를 클래스로 감싼 형태

    cout << arr.size() << endl;
    // cout << arr.at(10) << endl;
    // 범위를 벗어나면 예외를 던져줌.   
    cout << arr.front(); // 첫 번째 원소 (arr[0])
    cout << arr.back() << endl;  // 마지막 원소 (arr[arr.size() - 1])

    printArray(arr);

    std::array<int, 5> array_to_sort = {2, 5, 1, 4, 3};

    for (auto &el: array_to_sort)
    {
        cout << el << " ";
    }
    cout << endl;

    // 정렬 (begin과 end를 바꾸면 역순 정렬 가능)
    std::sort(array_to_sort.begin(), array_to_sort.end());

    for (auto &el: array_to_sort)
    {
        cout << el << " ";
    }

    return 0;
}