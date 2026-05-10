#include <iostream>
#include <string>

using namespace std;

class BasicMessenger {
 public:
  // 부모의 전송 함수 (virtual이 없어서 오버로딩 안됨)
  void send(string text) {
    cout << "기본 메신저: [문자] " << text << " 전송 완료" << endl;
  }
};

class SmartMessenger : public BasicMessenger {
 public:
  // 하이딩 발생: 부모의 send(string)를 가리고 새로운 인터페이스를 정의함
  // 부모의 send(string)
  void send(string text, string image) {
    cout << "스마트 메신저: [문자] " << text << " & [이미지] " << image
         << " 함께 전송" << endl;
  }

  // 부모의 기능을 using으로 쓰고 싶을 때 (해제하면 34줄 정상작동)
  // using BasicMessenger::send;
};

int main() {
  SmartMessenger myPhone;

  // 자식의 함수 호출
  myPhone.send("안녕하세요", "photo.jpg");

  // 부모의 함수 호출 시도 (컴파일 에러 발생)
  // myPhone.send("안녕?");
  // 에러 이유: SmartMessenger에서 이름이 'send'인 함수를 찾았기 때문에,
  // 컴파일러는 부모 클래스까지 올라가서 send(string)를 찾으려 하지 않음.
  //

  // 부모의 기능을 범위 지정 연산자로 쓰고 싶을 때 (보통은 using 사용)
  myPhone.BasicMessenger::send("부모 send 기능 부활");

  return 0;
}