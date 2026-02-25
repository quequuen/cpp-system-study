#include <iostream>
#include <vector>

using namespace std;

class Employee
{
    public: // 접근 지정자
    string name;
    string role;
    int age;

    void print()
    {
        cout << name << " (" << role << ", " << age << ") " << endl;
    }
};


int main()
{

    Employee em1 {"Hana", "employee", 28};
    em1.print();

    vector<Employee> em02;
    em02.resize(2); 

    for (auto &el : em02)
    {
        el.print();
    }

    
    return 0;
}