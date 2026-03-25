#include <iostream> 
#include "headers/Box.h"
#include <string>

int main()
{
    Box<int> intBox;
    intBox.setData(100);

    Box<std::string> strBox;
    strBox.setData("Hello Template");
    std::cout << strBox.getDate() << std::endl;;

    // Box myBox(500);

    return 0;
}