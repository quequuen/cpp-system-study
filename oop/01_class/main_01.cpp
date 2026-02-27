#include <iostream>
#include <string>
#include <vector>
#include <format>
#include <chrono>
#include <ctime>

using namespace std;

class Date
{
    private: // class는 접근 제한자를 무조건 가져야 함.
    int _month;
    int _day;
    int _year;

    public:

    // 생성자
    Date()
    {
        // 현재 시간 가져옴
        auto now = chrono::system_clock::now();
        std::time_t now_time = chrono::system_clock::to_time_t(now);

        // 로컬 시간으로 변환
        tm* local_time = localtime(&now_time);

        int year = local_time->tm_year + 1900;
        int month = local_time->tm_mon + 1; 
        int day = local_time->tm_mday;

        _month = month;
        _day = day;
        _year = year;

    }

    Date(const int &m, const int &d, const int &y)
    {
        _month = m;
        _day = d;
        _year = y;
    }

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

    string getDate() const 
    {
        return to_string(_month) + "." + to_string(_day) + "." + to_string(_year);
        // C++ 20 이상 가능
        // return std::format("{:02}.{:02}.{}", _month, _day, _year);
    }

    int getMonth() const 
    {
        return _month;
    }

    int getDay() const
    {
        return _day;
    }

    int getYear() const 
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

    cout << today.getDate() << endl;
    cout << today_c.getDate() << endl;

    Date today2;

    cout << today.getDate() << endl;

    return 0;
}