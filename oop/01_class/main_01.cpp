#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Date
{
    private: // class는 접근 제한자를 무조건 가져야 함.
    int _month;
    int _day;
    int _year;

    public:
    void setDate(const int &m, const int &d, const int &y)
    {
       _month = m;
       _day = d;
       _year = y; 
    }

    void setMonth(const int &m)
    {
        _month = m;
    }

    void setDay(const int &d)
    {
        _day = d;
    }

    void setYear(const int &y)
    {
        _year = y;
    }

    int getMonth()
    {
        return _month;
    }

    int getDay()
    {
        return _day;
    }

    int getYear()
    {
        return _year;
    }

    void copy(const Date &origin)
    {
        _month = origin._month;
        _day = origin._day;
        _year = origin._year;
    }

};

int main()
{
    Date today; 
    today.setDate(2, 26, 2026);

    cout << today.getDay() << endl;

    Date today_c;

    today_c.copy(today);



    return 0;
}