#include <iostream>

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

int main()
{
    // 함수 없이 단순 계산
    cout << 1+2 << endl;
    cout << 3+4 << endl;
    cout << 5+6 << endl;

    //함수 사용 계산
    cout << addNumbers(1, 2) << endl;
    cout << addNumbers(3, 4) << endl;
    cout << addNumbers(5, 6) << endl;

    cout << multiplyNumbers(1, 2) << endl;
    cout << multiplyNumbers(3, 4) << endl;
    cout << multiplyNumbers(5, 6) << endl;

    cout << printHelloUser("World") << endl;
    printHelloWorld();

    int a, b;

    cin >> a >> b;
    cout << "Sum: " << addNumbers(a, b) << endl;
    cout << "Product: " << multiplyNumbers(a, b) << endl;




    return 0;
}