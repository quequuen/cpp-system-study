#include <iostream>

using namespace std;

struct ArrayStruct
{
    int arr[10]{1,2,3,4,5,6,7,8,9,10};
};

void printSizeof(ArrayStruct arrStr)
{
    cout << sizeof(arrStr) << endl;
}

void printSizeofPtr(ArrayStruct *arrStr)
{
    cout << sizeof(*arrStr) << endl;
}


int main()
{

    int arr[10]{1,2,3,4,5,6,7,8,9,10};

    cout << arr << endl;
    // arr의 값이 아닌 arr의 첫번째 칸 주소가 출력
    // array는 사실 배열이 아니고 포인터임.

    char str[] = "hello";
    cout << *str << endl;

    ArrayStruct arrStr;

    cout << arrStr.arr[0] << endl;
    printSizeof(arrStr);

    ArrayStruct *arrStrPtr = &arrStr;

    printSizeofPtr(arrStrPtr);
    // printSizeof든 printSizeofPtr이든 결과는 40으로 동일.
    // 둘 다 포인터가 아닌 구조체가 그대로 감.


    return 0;
}