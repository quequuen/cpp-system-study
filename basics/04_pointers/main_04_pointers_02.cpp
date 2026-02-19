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
    // 구조체 원본으로 가서 사이즈 출력
    cout << sizeof(arrStr) << endl;
    // 인자로 넘어온 포인터 변수의 사이즈 출력(주소를 담은 크기 출력)
}


int main()
{

    int arr[10]{1,2,3,4,5,6,7,8,9,10};

    cout << arr << endl;
    // arr의 값이 아닌 arr의 첫번째 칸 주소가 출력

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