#include <iostream>

using namespace std;

class Value
{
    private:
    int _value;

    public:
    Value(int v)
    : _value(v)
    {}

    int getValue() const { return _value; }
    int& getValue() { return _value; }
    friend Value operator + (const Value &v1, const Value &v2);
    
    // friend 없이 멤버 함수로 만들려면 this를 사용해야 함.
    // Value operator + (const Value &v2)
    // {
    //     return Value (this->getValue() + v2.getValue());
    // }
};

Value operator + (const Value &v1, const Value &v2)
{
    return Value(v1.getValue() + v2.getValue());
}

int main ()
{
    Value v(1);
    Value v2(4);

    cout << (v + v2 + Value(5)).getValue() << endl;

    // 산술 연산자 오버로딩 안되는 것들: ?:, ::, sizeof, ., .*

    return 0;
}