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
    const char *name = "Zoe Han";
    const char *same_name = "Zoe Han";
    const char *diff_name = "Zoe Han";

    cout << (uintptr_t)name << endl;
    cout << (uintptr_t)same_name << endl;
    // 같은 값을 가진 두 변수는 같은 주소
    cout << (uintptr_t)diff_name << endl;


    return 0;
}