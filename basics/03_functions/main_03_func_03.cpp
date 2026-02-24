#include <iostream>
#include <string>
#include <array>
#include <functional>

using namespace std;

int returnTwo(int x)
{
    return 2;
}

int returnThree(int x)
{
    return 3;
}

bool isEven(const int &number)
{
    if(number % 2 == 0) return true;

    return false;
}

bool isOdd(const int &number)
{
    if(number % 2 != 0) return true;

    return false;
}

void printElements(const array<int, 10> &my_arr, bool (*check_flag)(const int&) = isEven)
{
    for (auto el : my_arr)
    {
        if(check_flag(el)) cout << el << " ";
        
    }
}

int main()
{

    int (*fxptr)(int) = returnTwo;

    cout << fxptr(0) << endl;

    fxptr = returnThree;

    cout << fxptr(0) << endl;

    std::array<int, 10> my_arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::function<bool(const int&)> functionptr = isEven;


    printElements(my_arr);
    printElements(my_arr, isOdd);

    cout << endl;

    return 0;
}