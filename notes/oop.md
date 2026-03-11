## 객체 지향 프로그래밍 (OOP, Object-Oriented Programming)

데이터와 로직을 객체 단위로 묶어 관리하는 패러다임. **캡슐화, 상속, 다형성, 추상화**라는 4대 원칙을 가짐. 이 원칙들은 코드의 재사용성, 유지 보수성, 확장성을 높이고 복잡성을 낮추기 위해 객체들의 공통 특징을 묶고, 내부 데이터를 보호하며, 유연하게 객체를 다룰 수 있게 함.

### 핵심 개념

- [클래스와 객체 상세 내용 (class.md)](./class.md)

### 객체들의 관계

- **상속 (Inheritance/ is-a)**: 상위 클래스(기본형)의 특징을 하위 클래스(파생형)가 물려받는 관계. "A는 B이다"라는 관계를 형성.
- **합성/구성 (Composition/ has-a)**: 한 객체가 다른 객체를 포함하며, 포함된 객체의 수명이 포함하는 객체의 수명과 일치하는 강한 결합 관계. (ex: 집-방)
- **집합 (Aggregation)**: 구성과 비슷하지만, 포함되는 객체가 포함하는 객체와 독립적으로 존재할 수 있는 더 약한 결합 관계.
- **의존 (Dependency)**: 한 객체가 다른 객체를 일시적으로 사용하여 동작하는 관계.
- **연관(Association)**: 두 객체가 서로 연관되어 상호작용하는 보다 일반적인 관계.

### 객체 간 상호작용

- 메시지 (Message): 객체 간의 통신은 메시지를 통해 이루어지며, 명령을 전달하여 데이터를 처리.
- 협력 (Collaboration): 객체들은 책임을 수행하고, 메시지를 주고받으며 협력하여 기능(공동체)을 구현.
- 역할 (Role): 특정 협력 내에서 객체가 수행하는 책임의 집합을 정의하여 유연성을 높임.

### 합성/구성 관계 (Composition / has-a)

**전체(Whole)**와 **부분(Part)**의 관계. 부분 객체의 생명 주기가 전체 객체의 생명 주기에 완전히 종속됨.

- 전체 객체(부모)가 소멸하면 그 안에 포함된 부분 객체(자식)도 함께 소멸.
- 부분 객체는 오직 하나의 전체 객체에만 속할 수 있으며, 외부에서 공유할 수 없는 경우가 많음. → 캡슐화 유지에 좋음.
- 부모 객체가 사라질 때 자식 객체도 확실히 정리되므로 메모리 누수 위험이 적음.
- 큰 시스템을 작은 부품 단위로 나누어 설계한 뒤 조립하는 방식(Modular) 가능.

```cpp
#include <iostream>
#include <string>

class Engine {
public:
    Engine() { std::cout << "엔진 생성" << std::endl; }
    ~Engine() { std::cout << "엔진 소멸" << std::endl; }
};

class Car {
private:
    std::string _model;
    Engine _engine; // 구성 관계: Car가 Engine을 직접 포함함

public:
    Car(std::string name) : _model(name) {
        std::cout << _model << " 자동차 생성" << std::endl;
    }
    ~Car() {
        std::cout << _model << " 자동차 소멸" << std::endl;
    }
};

int main() {
    {
        Car myCar("K5");
    } // myCar가 스코프를 벗어나면 _engine도 자동으로 소멸함

    return 0;
}
```

### 집합 관계 (Aggregation)

구성 관계와 마찬가지로 '전체-부분'의 관계를 나타내지만, 결합력이 훨씬 느슨한 관계.

- 전체 객체(Whole)가 소멸해도 부분 객체(Part)는 사라지지 않고 **독립적으로 존재**함.
- 하나의 부분 객체가 여러 개의 전체 객체에 속할 수 있음.
- 전체가 부분을 소유한다기보다는 필요할 때 빌려 쓰거나 잠시 **참조**하는 개념에 가까움.

```cpp
#include <iostream>
#include <string>
#include <vector>

class Teacher {
private:
    std::string _name;
public:
    Teacher(std::string name) : _name(name) {}
    std::string getName() const { return _name; }
};

class School {
private:
    std::string _schoolName;
    // 여러 명의 교사 주소를 저장하는 vector
    std::vector<Teacher*> _teachers;

public:
    School(std::string name) : _schoolName(name) {}

    // 교사를 명단에 추가
    void addTeacher(Teacher* t) {
        _teachers.push_back(t);
    }

    void showTeachers() const {
        std::cout << "[" << _schoolName << " 교사 명단]" << std::endl;
        for (const auto& t : _teachers) {
            std::cout << "- " << t->getName() << std::endl;
        }
    }

    ~School() {
        std::cout << _schoolName << "가 폐교 되었습니다." << std::endl;
        // School이 사라져도 벡터 안의 포인터들이 가리키는 Teacher 객체는 delete되지 않음.
    }

    int main() {
    Teacher* mrKim = new Teacher("김교사"); // 교사 객체 독립 생성

    {
        School mySchool("진격중");
        mySchool.addTeacher(mrKim); // 학교에 교사을 배정.
    } // 여기서 mySchool은 소멸.

    // 학교가 사라져도 김교사 객체는 여전히 존재.
    std::cout << mrKim->getName() << "님은 여전히 근무 중." << std::endl;

    delete mrKim; // 교사는 나중에 필요 없을 때 따로 해제
    return 0;
    }
};
```
