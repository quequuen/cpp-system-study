## 템플릿 (Templates)

코드를 찍어내는 틀. 데이터 타입에 의존하지 않는 범용적인 코드를 작성하기 위한 도구 (코드 설계도). 템플릿은 그 자체로 메모리를 차지하는 '객체'가 아니라, 컴파일러에게 전달하는 **코드 생성 지시서**임.

### 함수 템플릿 (Function Template)

특정 데이터 타입에 종속되지 않고, 로직(알고리즘)은 같지만 다루는 자료형만 바뀔 때 사용하는 함수 생성기.

- 함수 정의 바로 위에 template <typename T>를 붙여주고 인자들의 타입을 T로 정의.

```cpp
template <typename T>
T Max(T a, T b) {
    return (a > b) ? a : b;
}
```

- 명시적 호출 (Explicit)
  개발자가 직접 어떤 타입을 사용할지 명시.

  ```cpp
  cout << Max<int>(3, 7);       // T를 int로 확정해서 호출
  cout << Max<double>(3.5, 2.1); // T를 double로 확정해서 호출
  ```

- 암시적 호출 (Implicit/ Type Deduction)
  컴파일러가 인자로 들어온 값을 보고 타입을 스스로 추론.

  ```cpp
  cout << Max(10, 20);    // 인자가 int이므로 컴파일러가 T = int로 추론
  cout << Max(1.5f, 3.2f); // 인자가 float이므로 컴파일러가 T = float로 추론
  ```

- 서로 다른 두 타입을 인자로 받고 싶다면, 콤마(,)를 사용하여 여러 개의 인자를 정의할 수 있음.

  ```cpp
  template <typename T, typename U>
  void printPairs(T a, U b) {
      cout << a << " 와 " << b << endl;
  }

  int main() {
      printPairs(202544016, "한가연"); // T는 int, U는 const char*로 결정됨
  }
  ```

- 함수 템플릿 특수화 (Template Specialization)
  다른 타입은 다 똑같은 로직인데, 특정 타입 하나만 다르게 동작해야 하는 상황에 특수화를 사용함

```cpp
// 기본 템플릿
template <typename T>
T Add(T a, T b) { return a + b; }

// char* 타입에 대해서만 특수화
template <>
const char* Add(const char* a, const char* b) {
    // 문자열 두 개를 합치는 별도의 로직
    return "Combined String";
}
```
