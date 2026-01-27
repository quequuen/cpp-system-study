#include <iostream>

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
    // int x = 1, y = x + 2;

    // cout << y << endl;

    // namespace::util
    // cout << someSpace1::addSomething(1, 2) << endl;

    using namespace someSpace1;
    cout << addSomething(1, 2) << endl;

    using namespace someSpace1::someSpace2;
    cout << addTwoNum(1, 2) << endl;


    return 0;


}

