## 객체 지향 프로그래밍 (OOP, Object-Oriented Programming)

데이터와 로직을 객체 단위로 묶어 관리하는 패러다임.

### 클래스 (Class)와 객체 (Object)

- 클래스(Class): 객체를 만들기 위한 설계도.
- 객체(Object): 설계도를 바탕으로 메모리에 실제로 만들어진 실체.

```cpp
class Dog {
public:
    string name; // 멤버 변수
    void bark() { // 멤버 함수
        cout << name << ": 멍멍!" << endl;
    }
};

int main() {
    Dog myDog;       // 클래스(설계도)를 이용해 객체(실체) 생성
    myDog.name = "초코";
    myDog.bark();    // 초코: 멍멍!
}
```

### 접근 제한자 (Access Specifiers)

객체 지향 프로그래밍에서 클래스, 메소드, 변수 등 멤버에 대한 접근 권한을 설정하는 키워드. 데이터를 숨기는 캡슐화와 객체 간 결합도를 낮춰 코드의 보안성 및 유지 보수성을 높이며 C++에서는 세 가지 접근 제한자를 제공함.

- public: 클래스 밖에서도 누구나 접근 가능. (공개 서비스)
- private: 클래스 내부(멤버 함수)에서만 접근 가능. (내부 비밀)
- protected: 본인과 자신을 상속받은 자식 클래스까지만 접근 허용.
