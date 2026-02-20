#include<iostream>

using namespace std;

int main()
{
    int *int_ptr = nullptr;
    int **int_ptrptr = nullptr;

    int my_int = 2;

    int_ptr = &my_int;
    int_ptrptr = &int_ptr;

    cout << int_ptr << endl;
    cout << int_ptrptr << endl;
    cout << **int_ptrptr << endl;

    int rows = 3;
    int cols = 5;

    // 1. 행들을 관리할 이중 포인터 할당 (포인터 3개를 담는 배열)
    int** matrix = new int*[rows];

    // 2. 각 행에 실제 열(데이터 공간) 할당
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }

    // 3. 사용 (일반 2차원 배열처럼 사용 가능)
    matrix[1][2] = 100;

    // 4. 해제 (매우 중요: 만든 순서의 역순으로!)
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i]; // 각 행 먼저 삭제
    }
    delete[] matrix;       // 마지막에 행 포인터 배열 삭제

    return 0;
}