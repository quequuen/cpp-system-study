#include <iostream>
#include <initializer_list>

using namespace std;

class MyArray
{
private:
    unsigned _length = 0;
    int* _data = nullptr;

public:
    MyArray(unsigned length) : _length(length)
    {
        _data = new int[length];
    }

    MyArray(const std::initializer_list<int>& list) : MyArray((unsigned)list.size())
    {
        int count = 0;
        for (auto & el : list) _data[count++] = el;
    }

    // 복사 생성자 (깊은 복사) 
    MyArray(const MyArray& other) : MyArray(other._length)
    {
        for (unsigned i = 0; i < _length; ++i) _data[i] = other._data[i];
    }

    // 대입 연산자
    MyArray& operator = (const MyArray& my_array)
    {
        if(this == &my_array) return *this;
        delete[] _data;
        _length = my_array._length;
        if(my_array._data != nullptr) {
            _data = new int[_length];
            for(unsigned i=0; i < _length; ++i) _data[i] = my_array._data[i];
        }
        else _data = nullptr;
        return *this;
    }

    // 소멸자
    ~MyArray() { delete[] _data; }

    // 출력 연산자
    friend std::ostream& operator << (std::ostream& out, const MyArray& my_arr)
    {
        for (unsigned i = 0; i < my_arr._length; ++i)
            out << my_arr._data[i] << " ";
        return out;
    }
};

int main()
{
    MyArray my_array = {1, 2, 3, 4, 5};
    cout << my_array << endl; // 이제 출력됩니다!
    
    return 0;
}