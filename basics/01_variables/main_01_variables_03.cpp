#include <iostream>
// iostream 내 cstdint include
// #include <cstdint>

int main()
{
    using namespace std;

    cout << 33 / 5 << endl;
    // 정수끼리의 연산은 정수로 취급하기 때문에 6.6이 아닌 그냥 6이 나옴.
    cout << (float)33 / 5 << endl;

    std::int_fast8_t i(8); // 2 bytes짜리 데이터 타입으로 치환
    std::int8_t myint = 97; // 1 byte짜리 데이터 타입(char)으로 치환 
    // int를 썼기 때문에 정수라고 생각하겠지만 실제로는 char 데이터 타입을 인용

    cout << myint << endl;
    cout << i << endl;

    std::int_fast8_t fi(8);
    std::int_least64_t fl(8); // 최소 8 bytes

    cout << fi << endl;
    cout << fl << endl;

    // 8은 ASCII code로 치환하면 BackSpace(커서를 한 칸 뒤로 밀기)이기 때문에 공백으로 출력
    return 0;

}