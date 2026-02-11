#include <iostream>
#include <typeinfo>

int main()
{
   using namespace std;

    cout << typeid(nullptr).name() << endl; // nullptr_t
    int var1 = 1;
    cout << typeid(var1).name() << endl; // int

    float fl1 = 1.23f;
    double db1 = fl1; //nemeric promotion

    int int2 = 10000;
    char ch1 = int2; //numeric conversion
    cout << "int2: " << int2 << ", ch1: " << (int)ch1 << " " << "int값이 char에 다 안 들어감" << endl;

   return 0;
}