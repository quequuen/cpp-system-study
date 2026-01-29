#include <iostream>

using namespace std;

void printSomething(int x){
    x = 123;
    cout << x << endl;
}

int main(){
    int a = 123; // int(정수형) 타입의 a라는 이름의 변수를 선언(declaration)하고, 123이라는 숫자 값으로 초기화(initialization)
    a = 456; // a라는 메모리 공간 안에 456이라는 숫자 값을 대입(assignment)

    cout << a << endl;
    cout << &a << endl;   // &(주소 연산자) 사용으로 123이 저장된 메모리 주소 출력

    int b = 1;
    b = b + 3;
    
    cout << b << endl; // 4 출력

    int c = a;
    cout << c << endl; // 456 출력

    cout << b + c << endl; //460 출력
    cout << b << endl; // 4 출력

    int d;

    cout << d << endl; //쓰레기값 출력. 현재는 1이 출력됨.


    //전역 변수 vs 지역 변수

    int x = 0;

    cout << x << endl;
    printSomething(x);
    cout << x << endl;

    
    int li_x = 10; // literal value

    // 삼항 연산자
    int max_value = (a > li_x) ? a : li_x; // a와 li_x 중 더 큰 값을 max_value에 저장

    bool boolean_value = false;
    char char_value = 97;
    float float_value = 3.141592f;
    double double_value = 3.141592;

    cout << (boolean_value ? 1 : 0) << endl;
    cout << char_value << endl;
    cout << float_value << endl;
    cout << double_value << endl;

    // auto와 decltype(타입 추론)
    int type_test_x = 10;
    int& ref = type_test_x;

    auto auto_value = ref;          // a는 int (참조가 사라짐)
    decltype(ref) decltype_value = type_test_x;   // b는 int& (참조가 유지됨)

    cout << auto_value << endl;
    cout << decltype_value << endl;
    
    type_test_x = 20;

    cout << auto_value << endl;
    cout << decltype_value << endl;
    // decltype_value는 int가 아닌 int&이기 때문에 원본인 type_test_x의 값이 수정되면 수정된 값으로 출력됨.
    
    int init_a(123); //direct initialization
    int init_b{123}; //uniform initialization


    return 0;
}