#include <iostream>
#include <string>
#include <limits>


int main()
{
    const char char_arr [] = "Hello, World!";
    const std::string message {"Hello, World!"};
    // const std::string message = "Hello, World!";
    // c++ 에서는 string이 기본 자료형이 아니라 사용자 정의 자료형임.

    std::cout << char_arr << std::endl;
    std::cout << message << std::endl;

    std::cout << "NAME: " ;
    std::string name;
    // std::cin >> name;
    // 입력 버퍼에 남아있는 개행 문자를 제거하기 위해 추가
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 해당 방법은 입력 버퍼에 남아있는 개행 문자를 제거하는 방법 중 하나.
    std::getline(std::cin, name); //getline은 개행 문자를 만날 때까지 입력을 받음.
    // cin은 개행 문자를 버린 나머지 부분을 변수에 저장.
    // 따라서 공백이 포함된 문자열을 입력받을 때는 getline을 사용하는 것이 좋음.
    // std::cin.ignore()를 사용하지 않으면 getline이 바로 종료되어 빈 문자열이 저장됨.
    // cin 다음에 getline을 사용할 때는 이런 주의가 필요함.


    std::cout << "AGE: ";
    std::string age;
    // std::cin >> age;
    std::getline(std::cin, age);

    std::cout << "HELLO, " << name << "!" << std::endl;
    std::cout << "YOU ARE " << age << " YEARS OLD." << std::endl;
    std::cout << name.length() << std::endl;


    return 0;
}