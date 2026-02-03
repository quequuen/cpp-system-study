#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>


 int main()
 {
    using namespace std;

    float my_float(3.141592);
    float my_f = 3.141592f;
    double my_double;
    long double my_long_double;

    cout << sizeof(my_float) << endl;
    cout << sizeof(my_double) << endl;
    cout << sizeof(my_long_double) << endl;

    cout << numeric_limits<float>::max() << endl;
    cout << numeric_limits<double>::max() << endl;
    cout << numeric_limits<long double>::max() << endl;
    
    cout << numeric_limits<float>::min() << endl;
    cout << numeric_limits<double>::min() << endl;
    cout << numeric_limits<long double>::min() << endl;
    
    cout << numeric_limits<float>::lowest() << endl;
    cout << numeric_limits<double>::lowest() << endl;
    cout << numeric_limits<long double>::lowest() << endl;

    // min은 가장 작은 숫자의 절대값을 의미
    // lowest은 표현하는 범위의 최소값

    cout << 3.14 << endl;
    cout << 31.4e-1 << endl;
    cout << 31.4e-2 << endl;
    cout << 31.4e1 << endl;
    cout << 31.4e2 << endl;

    float my_fl(123456789.0f); // 10 significant digits
    
    cout << std::setprecision(16);
    // cout은 실수를 출력할 때 보통 6자리까지만 보여줌.
    // setprecision을 사용하게 되면 "기본 6자리만 보여주지 말고, double이 가진 정밀도를 최대한 살려서 16자리까 보여줘!"라고 하는 것.
    // 즉, 실수(floating-point)를 출력할 때 소수점을 몇 자리까지 보여줄지 정밀도를 설정하는 도구
    // 변수가 아닌 cout의 설정을 해주는 것
    cout << 1.0 / 0.3 << endl;
    cout << my_fl << endl;

    double my_d(0.2);

    cout << my_d << endl;
    cout << setprecision(17);
    cout << my_d << endl;

    double my_d1(1.0);
    double my_d2(0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1);

    cout << my_d1 << endl;
    cout << my_d2 << endl;
    // 이론적으로 둘의 값은 1.0으로 같아야 하나, my_d2는 부동소수점으로 인해 1.0이 아님.

    double zero = 0.0;
    double my_d3 = 2.0 / zero;
    double my_d4 = -2.0 / zero;
    double nan = zero / zero;

    cout << my_d3 << endl;  // inf(infinity)
    cout << my_d4 << endl;  // -inf
    cout << nan << endl;    // nan

    cout << my_d3 << " " << std::isinf(my_d3) << endl;  
    cout << my_d4 << " " << std::isinf(my_d4) << endl;  
    cout << nan << " " << std::isnan(nan) << endl; 
    cout << 0.2 << " " << std::isnan(0.2) << endl;   
    


    return 0;
 }