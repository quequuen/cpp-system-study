#include <iostream>

using namespace std;

void printArray(int array[], int length) {
  for (int i = 0; i < length; ++i) {
    cout << array[i] << " ";
  }
  cout << endl;
}

int main() {
  // 표준 C++에서는 배열 크기에 변수를 넣으려면 const를 붙여주는 것이
  // 안전
  const int length = 6;
  int array[length] = {5, 6, 3, 2, 4, 1};

  cout << "내림차순 선택 정렬 시작:" << endl;
  printArray(array, length);  // 초기 상태 출력
  cout << "------------------" << endl;

  for (int startIndex = 0; startIndex < length - 1; ++startIndex) {
    int biggestIndex = startIndex;

    // 현재 범위에서 가장 큰 값의 인덱스를 찾기
    for (int currentIndex = startIndex + 1; currentIndex < length;
         ++currentIndex) {
      if (array[biggestIndex] < array[currentIndex]) {
        biggestIndex = currentIndex;
      }
    }

    // 가장 큰 값을 현재 시작 위치의 값과 교체함
    int temp = array[biggestIndex];
    array[biggestIndex] = array[startIndex];
    array[startIndex] = temp;

    // 매 단계마다 정렬 결과를 출력
    cout << startIndex + 1 << "단계: ";
    printArray(array, length);
  }

  cout << "------------------" << endl;
  cout << "정렬 완료!" << endl;

  return 0;
}