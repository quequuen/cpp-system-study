#include <iostream>

using namespace std;

void changeValue(int &val)
// 참조 변수를 인자로 주어도 인자 자체가 참조 변수가 아닌 그냥 변수면 복사 개념임.
{
    val = 4;
    cout << "Change Value..." << endl << val << endl;
}

struct Employee
{
    int id;
    double test_score;
};


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

    int len;

    cin >> len;

    int *arr = new int[len];

    for (int i = 0; i < len; ++i)
    {
        int val = 0;
        cin >> val;
        arr[i] = val;
    }

    for (int i = 0; i <len; ++i)
    {
        cout << arr[i] << " ";
    }

    delete[] arr;

    int my_int = 2;

    int &my_ref = my_int;
    // 리터럴 사용 불가.
    // 초기화 필수
    // my_int를 같이 사용하고 있는 것처럼 옴.
    my_ref = 3;

    cout << my_int << endl;
    cout << my_ref << endl;
    cout << &my_int << endl;
    cout << &my_ref << endl;

    changeValue(my_ref);

    cout << my_int << endl;
    cout << my_ref << endl;


    Employee e1;
    e1.id = 1;
    e1.test_score = 91.3;

    Employee &ref = e1;
    e1.id = 2;

    Employee *e_ptr = &e1;
    e_ptr->id = 3;
    (*e_ptr).id = 10;



    return 0;
}