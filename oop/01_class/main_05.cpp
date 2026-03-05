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

    Value operator - () const{ return Value(-_value); }
    bool operator ! () const { return (_value == 0)? true : false; }

    // operator << 의 왼쪽의 피연산자는 std::ostream이지 Value 객체가 아님. 따라서 멤버 함수로 만들 수 없고 반드시 전역 함수로 만들어야 함.
    friend std::ostream& operator << (std::ostream &out, const Value &v)
    {
        out << v._value;

        return out;
    };

    friend std::istream& operator >> (std::istream &in, Value &v)
    {
        in >> v._value;

        return in;
    }

};

Value operator + (const Value &v1, const Value &v2)
{
    return Value(v1._value + v2._value);
}


int main ()
{
    Value v(1);
    Value v2(4);

    cout << (v + v2 + Value(5)).getValue() << endl;

    // 산술 연산자 오버로딩 안되는 것들: ?:, ::, sizeof, ., .*

    Value v3 = v + v2;

    cout << "결과: " << v3 << endl;

    Value v_in(0);

    cout << "Value 객체의 value를 설정해주세요: ";
    cin >> v_in;

    cout << "입력값: " << v_in << endl;


    return 0;
}