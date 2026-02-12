#include <iostream>
#include <string>

using namespace std;

struct User
{
    double height;
    float weight;
    string id;
    int age;
    string name;

    void print()
{
    cout << "Hello, " << name << "." << endl;

}
};

User printUser()
{
    User user{100.0, 22.0, "id", 27, "Name Han"};

    return user;
}

struct Party 
{
    User user1;
    User user2;
    User user3;
};



int main()
{
    User user1;
    user1.age = 27;
    user1.name = "Name Han";
   
    User user2{100.0, 22.0, "id", 27, "Name Han"};
    user2.print();

    User user3;
    User user_from_func = printUser();
    user_from_func.print();

    return 0;
}