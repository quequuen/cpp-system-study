// TCP 기본 구조 → Boost.Asio의 동기식(synchronous) TCP 서버
// TCP 서버가 어떻게 만들어지는지, 클라이언트를 어떻게 받는지, 데이터를 어떻게
// 보내는지 학습
// 서버 프로그램 시작 → 13번 포트에서 기다림 → 클라이언트 접속 → TCP 연결 생성 →
// "Hello From Server" 전송 → 다음 클라이언트 기다림 → 반복

#include <boost/asio.hpp>
// Boost.Asio를 사용하기 위한 헤더
// 네트워크 프로그래밍에 필요한 것들이 들어있음.
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

int main() {
  try {
    boost::asio::io_context io_context;
    // Boost.Asio가 비동기 작업이나 I/O 작업을 관리하기 위해 사용하는 실행
    // 컨텍스트.

    tcp::endpoint endpoint(tcp::v4(), 13);
    // 네트워크에서 통신할 대상의 주소 정보 (IP 주소 + Port)
    // IPv4 + 13번 포트 사용 엔드포인트 생성
    // 실제 서버에서는 보통 애플리케이션에 맞는 포트를 사용하고, 13번 포트는
    // 학습 예제로 전통적으로 많이 등장하는 번호.
    tcp::acceptor acceptor(io_context, endpoint);
    // 클라이언트의 연결 요청을 받아들이는 객체

    std::cout << "Server started\n";

    for (;;) {  // = while(ture)
      // 서버는 일반적으로 다양하고 많은 클라이언트의 접속을 허용해야 하기
      // 때문에 무한히 반복
      // 현재 코드는 한 번에 한 클라이언트를 처리하는 단순한 서버
      tcp::socket socket(io_context);
      // 연결된 클라이언트와 통신하는 객체

      std::cout << "Waiting for client...\n";

      boost::system::error_code ec;
      // Asio 작업에서 발생할 수 있는 오류를 저장할 객체
      acceptor.accept(socket, ec);
      // 실제로 클라이언트의 연결을 받아들이는 작업
      // 이 부분을 호출하면 클라이언트가 연결할 때까지 현재 스레드가 대기
      // accept()가 끝나기 전까지 다음 코드로 내려가지 않아서 동기 방식

      if (ec) {
        std::cerr << "Accept error: " << ec.message() << '\n';
        continue;
      }

      std::cout << "Client connected\n";

      const std::string message = "Hello From Server\n";

      boost::asio::write(socket, boost::asio::buffer(message), ec);

      if (ec) {
        std::cerr << "Write error: " << ec.message() << '\n';
      }
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}