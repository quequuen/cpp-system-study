#include <iostream>

using namespace std;

int main()
{
    double my_double = 7.0;
    double *ptr = &my_double;

    cout << uintptr_t(ptr-1) << endl;
    cout << uintptr_t(ptr) << endl;
    cout << uintptr_t(ptr+2) << endl;

    int arr[10]{1,2,3,4,5,6,7,8,9,10};

    int *arr_ptr = arr;

    for (int value : arr)
    {
        // cout << arr[value-1] << ": " << (uintptr_t)&arr[value-1] << endl;
        cout << *(arr_ptr+(value-1)) << ": " << (uintptr_t)(arr_ptr+(value-1)) << endl;
    }

    cout << sizeof(arr) << endl;

    char str[] = "Hello, blank!";

    for (char* ptr = str; *ptr != '\0'; ++ptr) {
        cout << *ptr; 
    }

    return 0;
}