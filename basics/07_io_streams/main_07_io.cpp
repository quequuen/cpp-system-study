#include <iostream> // cout, cin, endl 등 입출력 스트림 라이브러리 포함
#include <cstdio> // printf, scanf 함수 사용을 위한 C 표준 입출력 라이브러리 포함

int main(){

    using namespace std;
    // std namespace 사용 선언
    // 파이썬으로 치면 메소드를 함수화 시켜 import 하는 것과 비슷함.
    // ex) from math import pi
    // -> math.pi 대신 pi로 바로 사용 가능

    int x = 123;
    double y = 3.141592;

    cout << "I love this!\n" << endl;
    // endl: end line, 줄바꿈 문자 출력 후 버퍼 비우기 (출력 대기 중인 내용 강제 출력)

    cout << "x = " << x << ", pi = " << y << endl;
    cout << "abc" << "\t" << "def" << endl;

    cout << "\a"; // \a: 경고음 출력
    
    int a = 1; // 입력을 받기 전에는 입력 받은 값을 저장할 변수를 이미 선언해놓아야 함

    cout << "Before input, a = " << a << endl;
    cout << "Enter an integer: ";

    cin >> a; // 사용자로부터 정수형 입력을 받아 a 변수에 저장
    cout << "You entered: " << a << endl;
    return 0;
}