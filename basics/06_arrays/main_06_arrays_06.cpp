#include <iostream>
#include <vector>

using namespace std;

int main() 
{
    vector<int> v = {1, 2};
    int* ptr = &v[0]; // v[0]의 주소를 기억해둠
    
    cout << &v << endl;
    cout << ptr << endl;
    cout << *ptr << endl;
    cout << &v[0] << endl;
    
    v.push_back(3); // 만약 여기서 용량이 꽉 차서 이사를 갔다면?
    // 이제 ptr이 가리키는 주소는 이미 삭제된 '옛날 집' 주소

    cout << &v << endl;
    cout << ptr << endl;
    cout << *ptr << endl;
    cout << &v[0] << endl;


    
    return 0;
}