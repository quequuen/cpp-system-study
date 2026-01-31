#include <iostream>
#include <cmath>
// 수학 함수 라이브러리 (pow, sqrt, abs, round, ceil, float)
#include <limits>
// 사용 중인 시스템에서 특정 자료형이 가질 수 있는 최대값, 최소값 등을 확인하고 싶을 때 사용. (numeric_limits<T>)
// 오버플로우(Overflow) 방지를 위한 조건을 짤 때 필수적.

int main()
{
    using namespace std;

    short short_value = 1; // 2 bites = 16 bits
    
    // cmath 예시
    double root = std::sqrt(16.0); // 4.0
    double power = std::pow(2, 10); // 1024.0

    // limits 예시
    int max_int = std::numeric_limits<int>::max();
    

    cout << sizeof(short) << endl;
    cout << std::pow(2, sizeof(short) * 8 - 1) - 1 << endl;
    // 첫번째 -1은 부호를 나타내는 비트 때문에 1 비트를 하나 빼준 것
    // 두번째 -1은 0을 표현하는 부분을 뺌

    cout << "2의 10승: " << power << endl;
    cout << "int의 최대값: " << max_int << endl;
    cout << std::numeric_limits<int>::max() << endl;
    cout << std::numeric_limits<int>::min() << endl;
    cout << std::numeric_limits<int>::lowest() << endl;

    short_value = 32767;
    short_value = short_value + 1;

    cout << "short_value 오버플로우 발생 : " << short_value << endl;
    // short_value 오버플로우 발생: -32768 

    return 0;
}