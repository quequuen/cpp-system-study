#include <iostream>

using namespace std;

enum Student
{
    STU_FIR,
    STU_SEC,
    STU_THI,
    NUM_STUDENTS,
};

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

    return 0;
}