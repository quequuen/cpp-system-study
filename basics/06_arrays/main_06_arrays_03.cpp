#include <iostream>

using namespace std;

    cout << "내림차순 선택 정렬" << endl;
    for(int startIndex = 0; startIndex < length - 1; ++startIndex)
    {
        int biggestIndex = startIndex;

        for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
        {
            if(array[biggestIndex] < array[currentIndex])
            {
                biggestIndex = currentIndex;
            }
        }

        int temp = array[biggestIndex];
        array[biggestIndex] = array[startIndex];
        array[startIndex] = temp;

        printArray(array, length);
    }
    return 0;
}