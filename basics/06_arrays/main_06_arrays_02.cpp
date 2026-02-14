#include <iostream>

int main()
{
    using namespace std;

    int arr[] = {10, 20, 30, 40, 50};
    
    const int num_arr = sizeof(arr)/sizeof(int);
    // 함수에 인자로 보낸 arr는 포인터 변수가 넘어간 것이기 때문에 main에 구현한 값과 다를 수 있어서 size를 따로 넘겨주는 것.

    int sum_value = 0;
    int max_value = arr[0];
    int min_value = arr[0];


    for(int i=0; i < num_arr; ++i)
    {
        sum_value += arr[i];
        max_value = (max_value < arr[i])? arr[i] : max_value;
        min_value = (min_value > arr[i])? arr[i] : min_value;
    }

    double avg_value = static_cast<double>(sum_value) / num_arr;

    cout << "합계: " << sum_value << endl;
    cout << "최대값: " << max_value << endl;
    cout << "최소값: " << min_value << endl;

    return 0; 
}