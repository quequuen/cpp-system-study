#include <iostream>
using namespace std;

class Parents
{
    private:
    int _pnum;

    public:

    Parents(const int& pnum)
    : _pnum(pnum)
    {}

    void setValue(const int& num)
    {
        cout << "Parents's setValue" << endl;
        _pnum = num;
    }

    int getValue()
    {
        cout << "Parents's getValue" << endl;
        return _pnum;
    }
};

class Sister : public Parents   
{
    private:
    double _snum;

    public:
    // Sister 클래스가 생성 될 때는 내부적으로 Parents가 같이 생성됨.
    // Sister(){}

    Sister(const int& pnum, const double& snum)
    //: _pnum(pnum), _snum(snum) // 에러: _pnum은 private. 
    : Parents(pnum), _snum(snum)
    {
        // Parents의 생성자가 없을 경우.
        Parents::setValue(pnum);
        setValue(snum);
    }

    void setValue(const double& num)
    {
        cout << "Sister's setValue" << endl;
        _snum = num;
    }

    double getValue()
    {
        cout << "Sister's getValue" << endl;
        return _snum;
    }

};

class Brother: public Parents   
{
    private:
    double _bnum;

    public:
    void setValue(const double& num)
    {
        cout << "Brother's setValue" << endl;
        _bnum = num;
    }

    double getValue()
    {
        cout << "Brother's getValue" << endl;
        return _bnum;
    }
};

class Baby: public Parents
{
    private: 
    double _banum;

    public:
    void setValue(const double& num)
    {
        cout << "Baby's setValue" << endl;
        _banum = num;
    }

    double getValue()
    {
        cout << "Baby's getValue" << endl;
        return _banum;
    }

};

int main()
{
    // Parents p;
    // Sister s;

    Sister s(0, 10);

    // Name Hiding(Parents의 setValue는 이 방식으로 호출 못함.)
    s.setValue(1);
    s.Parents::setValue(2);

    Sister s2(1, 2);
    cout << s.getValue() << endl; 

    
    return 0;
}