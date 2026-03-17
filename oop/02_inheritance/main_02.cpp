#include <iostream>

using namespace std;

class Parent {
protected:
    int protectedValue = 10;
};

// private 상속: 부모의 모든 유산을 자식의 private 영역으로 가져옴
class Child : private Parent {
public:
    void access() {
        // 자식 내부에서는 부모의 protected 멤버에 접근 가능
        cout << protectedValue << endl; 
    }
};

class GrandChild : public Child {
public:
    void access() {
        // cout << protectedValue << endl; // Child에 private으로 Parent를 상속 받았기 때문에
        // 손자 객체는 접근 불가.
    }
};

int main() {
    Child c;
    // c.protectedValue; 
    c.access(); // 내부 함수를 통해서만 확인 가능
}