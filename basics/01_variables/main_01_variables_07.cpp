#include <iostream>

extern void printMessage();
// void printMessage(); // test.cpp에 정의된 함수를 외부에서 사용하겠다는 선언(윗줄과 같은 의미)
// 이걸 일일이 파일마다 쓸 수 없으니까 이걸 인터페이스화 한 게 헤더 파일임. 

// auto add(auto x, auto y) -> 이건 안됨.
auto autoAdd(int x, int y)
{
    return  x + y;
}
// 오버로딩
auto autoAdd(double x, double y)
{
    return x + y;
}

using namespace std;


void doSomething()
{
    static int count = 0; // 정적 지역 변수
    // static: (변화∙움직임이 없이) 고정된[고정적인]
    // 해당 변수 count가 os로부터 받은 메모리 공간이 정적이라는 뜻(프로그램이 종료될 때까지 유지)
    // 정적 지역 변수는 초기화가 한 번만 이루어지고, 쓰레기 값이 아닌 zero initialization이 됨.
    // 다른 cpp 파일에서 접근 불가능(지역 변수이기 때문)

    ++count;
    cout << "doSomething 호출 횟수: " << count << endl;
    cout << "count 주소: " << &count << endl;
}

int a = 0;

namespace space1
{
    int a = 1;
}

namespace space2
{
    int a = 2;
}

int main() 
{
    int a = space1::a;
    cout << "space1::a: " << a << endl;
    space2::a;

    cout << ::a << endl; // 전역 변수 a에 접근

    doSomething();
    doSomething();
    doSomething();

    auto auto_a = 10;
    auto auto_b = 123.0;
    auto auto_c = 1 +2.3;
    auto auto_add = autoAdd(1.3, 2.0);
    

    return 0;
}