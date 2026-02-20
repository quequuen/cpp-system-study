#include <iostream>

using namespace std;

int main()
{

    int *int_ptr = new (std::nothrow) int{12};
    // std::nothrow를 해주면 에러를 견딜 수 있음

    cout << int_ptr << endl;    // 변수가 저장하고 있는 값
    cout << &int_ptr << endl;   // 포인터 변수 자체의 주소
    cout << *int_ptr << endl;

    delete int_ptr; // new로 선언한 변수를 기억해두고 프로그램 종료 전 알아서 반납해가지만
    //이렇게 자체적으로 반납 가능.

    cout << "After delete: " << endl;

    cout << int_ptr << endl;    
    cout << &int_ptr << endl;   
    cout << *int_ptr << endl;

    return 0;
}