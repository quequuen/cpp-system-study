#include <iostream>
#include <cstddef>

int main()
{
    using namespace std;
    // void a;
    // void는 메모리를 차지하지 않기 때문에 선언 불가

    char a = 'a';
    int b = 123;

    cout << &a << endl;
    // 이렇게만 적어주면 std::cout은 char 타입의 주소는 주소로 인지하지 않고
    // 문자열의 시작점으로 인식함(지나친 친절함)
    cout << (void*)&a << endl;
    // 문자열의 주소를 출력할 시, 이런 식의 형 변환이 필수임.
    cout << &b << endl;

    

    void *myvoid;
    // 이건 포인터를 사용하여 주소를 받기 때문에 선언 가능
    // 주소값의 크기는 데이터 타입과 상관없이 모두 동일하다.
    // void*라는 바구니는 "이게 뭘 가리키는지는 나중에 생각하고, 일단 8바이트짜리 주소값만 담아줘!"라는 용도로 설계

    myvoid = (void*)&a;
    myvoid = (void*)&b;
    // 일반 포인터를 void*에 넣을 때는 명시적 캐스팅이 필수는 아님.(자동으로 형변환)
    

    // cout << *myvoid << endl;
    cout << *(int*)myvoid;
    // void*의 치명적인 약점(⭐️)
    // void*는 주소를 담을 수는 있지만 그 주소에 가서 값을 읽어오는 것은 불가능.
    // 컴퓨터가 주소지에 도착했는데, 거기서 몇 바이트를 읽어야 할지(char면 1, int면 4)모르기 때문임.
    // 다시 값을 읽으려면 반드시 원래 타입으로 다시 형변환 해야 함.


    
    
    // 결론: 데이터 타입이 다르고, 그 다음에 데이터 타입의 사이즈가 다르더라도 그 데이터의 주소를 표현하는 데이터 양은 동일.
    
    char *ptr_a = &a;
    int *ptr_b = &b;

    double *ptr_null = nullptr;

    if (ptr_null != nullptr)
    {
        // do something
    }

    std::nullptr_t nptr;
    // nullptr만 받아야 하는 파라미터
    
    
    return 0;
}