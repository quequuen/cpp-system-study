#include <iostream>
#include <string>
#include "headers/Leader.h"
#include "headers/Imployee.h"

int main()
{
    // std::string name;

    Leader l1("Levi");
    l1.setName("Levi Arkerman");
    // std::cout << l1.getName() << std::endl;
    std::cout << l1 << std::endl;
    
    Imployee i1("Eren");
    // std::cout << i1.getName() << std::endl;
    std::cout << i1 << std::endl;

    i1.doSomething();


    return 0;
}