#include <iostream>

class Parent 
{
public:
    virtual Parent* clone() { return new Parent(); }
};

class Child : public Parent
{
public:
    // 반환형을 Parent*로 유지해야 함. (override)
    // Parent* clone() override { return new Child(); }

    Child* clone() override { return new Child(); }
}; 


int main()
{
    Child* c1 = new Child();
    // clone이 Parent*를 반환함로 Child*에 담으려면 캐스팅이 필요함.
    Child* c2 = static_cast<Child*>(c1->clone());
    // 공변 반환값에 의해 형변환 없이 바로 Child* 타입으로 받을 수 있음.
    Child* c3 = c1->clone();


    return 0;
}