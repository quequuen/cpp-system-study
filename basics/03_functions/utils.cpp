#include <iostream>
#include <string>

using namespace std;

int addNumbers(int a, int b)
{
    int sum = a + b;

    return sum;
}

int subtractNumbers(int a, int b)
{
    int difference = a - b;

    return difference;
}

int multiplyNumbers(int a, int b)
{
    int product = a * b;

    return product;
}

string printHelloUser(string name)
{
    return "Hello, " + name + "!";
}

void printHelloWorld()
{
    cout << "Hello, World!" << endl;
}