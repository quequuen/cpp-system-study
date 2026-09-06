#include <iostream>
#include <vector>
#include <functional>

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

class Son: public Parent
{
public:
    int _j = 1;
    virtual void print() override
    {
        cout << "I'm Son." << endl;
    }
};

void doSomething(Parent &p)
{
    p.print();
}

int main()
{
    Son s;
    Parent p;
    p = s;
    // 의도적인 객체 잘림(슬라이싱)
    // 자식 객체가 부모 객체보다 더 많은 내용을 담고 있기 때문

    p.print();
    doSomething(s);

    std::vector<Parent*> my_vec;
    my_vec.push_back(&p);
    my_vec.push_back(&s);

    for (auto & el : my_vec)
        el->print();


    return 0;

}