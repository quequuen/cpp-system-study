#include <iostream>

using namespace std;

// 전방 선언 (foward declaration)
class Friend;

class Friend2
{
    private:
    int _value = 2;

    public:
    void doSomething(Friend& f);
};

class Friend
{
    private:
    int _value = 1;

    friend void Friend2::doSomething(Friend& f);

};


void Friend2::doSomething(Friend& f)
{
    cout << f._value << endl;

};



int main()
{

    Friend f;
    Friend2 f2;
    f2.doSomething(f);

    return 0;
}