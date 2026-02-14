#include <iostream>

using namespace std;

enum Student
{
    STU_FIR,
    STU_SEC,
    STU_THI,
    NUM_STUDENTS,
};

void printAddr(int arr_param[20])
{
    cout << "함수 내 sizeof(arr): " << sizeof(arr_param) << endl;     // 함수 내 sizeof(arr): 8
    // 배열 쇠퇴: 컴파일러는 내부적으로 void printAddr(int* arr)로 해석
    // C++은 배열을 함수 파라미터로 넘길 때 배열 전체를 복사하지 않고, 배열의 첫 번째 요소를 가리키는 '포인터'만 넘김
    // 관례적으로 배열을 함수에 넘길 때는 배열의 크기를 별도의 인자로 함께 넘겨줌.
    // void printAddr(int arr[], int size)
    // 하지만 이 함수 내의 &arr와 main의 &students_scores는 다른 값. 함수 인자로 넘어오는 건 해당 배열의 첫번째 요소를 가리키는 포인터 변수. 주소값을 저장하고 있는 '포인터 변수'의 주소.
    // main의 students_scores는 집 자체, arr을 읽으면 집 주소, &arr은 그 메모지가 놓여있는 위치.
    cout << "printAddr 내 배열 주소" << endl;
    cout << &arr_param[0] << endl;
    cout << &arr_param[1] << endl;
    cout << &arr_param[2] << endl;
    arr_param[0] = 999;
    // 원본의 값도 수정.
}

int main()
{
    int one;
    int arr[5];

    cout << sizeof(one) << endl;
    cout << sizeof(arr) << endl;

    arr[0] = 100;
    arr[1] = 101;
    arr[2] = 102;
    arr[3] = 103;
    arr[4] = 104;
    // 5칸의 배열에 6번째 요소 추가
    // arr[5] = 105; 

    for (int i=0; i < 5; i++)
    {
        cout << arr[i] << endl;
    }

    int students_scores[NUM_STUDENTS];
    students_scores[STU_FIR] = 100;
    students_scores[STU_SEC] = 50;
    students_scores[STU_THI] = 80;

    cout << &students_scores << endl;   //0x16fa3e7e8
    // int 배열이라서 메모리 주소가 4씩 증가함
    cout << &students_scores[0] << endl;    //0x16fa3e7e8
    cout << &students_scores[1] << endl;    //0x16fa3e7ec
    cout << &students_scores[2] << endl;    //0x16fa3e7f0
    cout << &students_scores[3] << endl;    //0x16fa3e7f4
    // 메모리 주소가 연속적임 

    printAddr(students_scores);

    return 0;
}