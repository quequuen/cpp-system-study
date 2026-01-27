#include <iostream>

#define MY_NUMBER 2
// define은 상수를 지정할 때 사용.
// MAX_VALUE, MIN_VALUE 등에 사용하는 문서 편집기.
#define MAX_NUMBER(a, b) ((a > b) ? (a) : (b))
// 하지만 요즘에는 algorithm 네임스페이스도 있고 함수로 구현하면 돼서 max, min은 이런 식으로 안함.
#define NAME "가연"


namespace someSpace1 
{
    int addSomething(int a, int b)
    {
        return a + b;
    }

    // namespace 안 namespace
    namespace someSpace2
    {
        int addTwoNum(int a, int b){
            return a + b;
        }
    }

}

namespace someSpace3
{
    int addThreeNum(int a, int b, int c)
    {
        return a + b + c;
    }

}

using namespace std;

int main(){
    // int x = 1;
    // int y = x + 2;
    int x = 1, y = x + 2;

    cout << y << endl;

    // namespace::util
    cout << someSpace1::addSomething(1, 2) << endl;



    using namespace someSpace1;
    cout << addSomething(1, 2) << endl;

    using namespace someSpace1::someSpace2;
    cout << addTwoNum(1, 2) << endl;

    cout << MY_NUMBER << endl;

    #ifdef NAME
        cout << NAME << endl;
    #endif

    #ifndef NAME
    // notdefine
        cout << "비회원" << endl;
    #endif

    //혹은

    #ifdef NAME
        cout << NAME << endl;
    #else
        cout << "비회원" << endl;
    #endif





    return 0;


}

