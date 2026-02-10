#include <iostream>

namespace space1
{
    int a = 1;
}

namespace space2
{
    int a = 2;
}

int main() 
{
    int a = space1::a;
    std::cout << "space1::a: " << a << std::endl;
    space2::a;

    return 0;
}