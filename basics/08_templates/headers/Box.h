#include <iostream>

template <typename T>
class Box 
{
private: 
    T data;  
public:
    void setData(T value) { data = value; }
    T getDate() { return data; }
}; 

// template <typename T>
// void Box<T>::setData(T value)
// {
//     data = value;
// }