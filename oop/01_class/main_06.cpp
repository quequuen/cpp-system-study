#include <iostream>
#include <cassert>

using namespace std;

class StringClass
{
    public:
    char *_data = nullptr;  // 문자열을 저장해야 되는 메모리에 대한 포인터.
    int _length = 0;

    public:
    StringClass(const char *src = "")
    {
        // 문자열이 비어있을 시 assert
        assert(src);

        _length = std::strlen(src) + 1; // 문자열의 마지막이라는 것을 표현하기 위한 null character 추가용 +1
        _data = new char[_length];

        for (int i=0; i < _length; ++i)
        {
            _data[i] = src[i];
        }
        _data[_length - 1] = '\0';
    }

    StringClass(const StringClass &src)
    {
        cout << "Copy constructor(Deep Copy)" << endl;

        _length = src._length;

        if(src._data != nullptr)
        {
            // 1. 새로운 메모리 할당
            _data = new char[_length];

            // 2. 실제 문자열 내용을 복사
            for(int i=0; i<_length; ++i)
            {
                _data[i] = src._data[i];
            }
        }
        else _data = nullptr;
    } 

   StringClass& operator = (const StringClass & src)
   {

    // shallow copy
    // this -> _data = src._data;
    // this -> _length = src._length;

    cout << "Assignment operator" << endl;

    if(this == &src) return *this; // self-assignment 금지

    delete[] _data;
    _length = src._length;

    if(src._data != nullptr)
    {
        _data = new char[_length];

        for(int i=0; i < _length; ++i)
        {
            _data[i] = src._data[i];
        }

    }
    else
    {
        _data = nullptr;
    }

    return *this;
    
   }

    ~StringClass()
    {
        delete[] _data;
    }
    
    char* getString(){ return _data; };
    int getLength(){ return _length; };
};

int main()
{

    StringClass string("Hello");

    cout << (int*)string._data << endl;
    cout << string.getString() << endl;

    {
        StringClass copy = string;
        cout << (int*)copy._data << endl;
        cout << copy.getString() << endl;

        // copy는 string 객체를 얕은 복사함
        // 1. string 객체와 copy 객체의 _data가 메모리의 같은 위치를 가리키게 됨.
        // 2. main 함수 안의 중괄호가 끝나는 순간, 지역 변수인 copy의 소멸자 호출 → _data를 free.
        // 3. 똑같이 main 함수가 종료될 때 원래 있던 string 객체의 _data 메모리 주소를 free하려고 시도함.
        // → double free 에러
        // 해결 방법: 깊은 복사 구현
    }

    // cout << string.getString() << endl;

    StringClass str = string;
    StringClass str2;
    str2 = string;
    return 0;
}