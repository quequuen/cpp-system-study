#include "headers/Person.h"
#include <iostream>

using namespace std;

void Person::doSomething() const
{
    cout << _name << " is doing something...🫡" << endl;
}