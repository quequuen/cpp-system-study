#include <iostream>
#include <typeinfo>

enum Grade
{
    F = 1,
    D,
    C,
    B, 
    A = 5
};

int main()
{
    using namespace std;

    Grade grade_a = A; 
    Grade grade_b(B);
    Grade grade_c{C};
    int my_grade = grade_a;

    cout << my_grade << endl;
    // Grade my_grade = 3;
    // Grade와 int 타입이라서 타입이 맞지 않음.
    // Casting 필요
    Grade grade = static_cast<Grade>(3);

    cout << grade << endl;

    enum class Color
    {
        RED,
        GREEN,
        BLUE
    };

    Color color1 = Color::BLUE;
    Color color2 = Color::GREEN;

    if (color1 == color2)
        cout << "Same Color" << endl;
    
    return 0;
}