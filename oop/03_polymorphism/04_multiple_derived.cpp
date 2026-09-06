#include <iostream>
#include <string>

using namespace std;

class Parent
{
public: 
    int _i = 0;

    virtual void print()
    {
        cout << "I'm Parent." << endl;
    }
};

class Child: public Parent
{
public:
    int _j = 1;
    virtual void print() override
    {
        cout << "I'm Child." << endl;
    }
};

class SecondChild: public Parent
{
public:
    int _k = 1;
    virtual void print() override
    {
        cout << "I'm SecondChild." << endl;
    }
};

void doSomething(Parent &p)
{
    p.print();
}
int main()
{

    Child c1;
    c1._j = 222;
    Parent *p = &c1;

    // 부득이하게 p를 다시 c1 형으로 바꿔야 할 때.
    auto *parent_to_c1 = dynamic_cast<Child*>(p);

    if (parent_to_c1 != nullptr)
        cout << parent_to_c1->_j << endl;
    else
        cout << "Failed" << endl;

    // 특별한 경우가 아니라면 복잡하기 때문에 잘 사용하지 않음.

    return 0;
}