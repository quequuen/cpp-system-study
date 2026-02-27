#include <iostream>

using namespace std;

class Basic
{
private:
    int _id;    

public:
    Basic(int id)
    {
        this->setId(id);
        
        cout << this << endl;
    }

    void setId(int id)
    {
        _id = id;
    }

    int getId()
    {
        return _id;
    }

};



int main()
{
    Basic b1(0), b2(1);
    b1.setId(1);
    b2.setId(2);
    
    
    return 0;
}