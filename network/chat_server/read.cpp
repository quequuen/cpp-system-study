
// TCP 기본 구조 → Boost.Asio의 동기식(synchronous) TCP 서버
// Client ↔ Server 양방향 통신
//
// 서버 프로그램 시작
// → 13번 포트에서 기다림
// → 클라이언트 접속
// → TCP 연결 생성
// → Client가 보낸 메시지 수신
// → Server가 응답 전송
// → 연결 종료
// → 다음 클라이언트 기다림

#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

int main() {
  try {
    boost::asio::io_context io_context;
    // Boost.Asio의 I/O 작업을 관리하는 실행 컨텍스트

    tcp::endpoint endpoint(tcp::v4(), 13);
    // IPv4 + 13번 포트를 사용하는 서버 엔드포인트

    tcp::acceptor acceptor(io_context, endpoint);
    // 클라이언트의 TCP 연결 요청을 받아들이는 객체

    std::cout << "Server started\n";

    for (;;) {
      tcp::socket socket(io_context);
      // 연결된 Client와 실제 데이터를 주고받는 socket

      std::cout << "Waiting for client...\n";

      boost::system::error_code ec;

      acceptor.accept(socket, ec);
      // Client가 연결할 때까지 대기
      // 연결이 들어오면 socket과 연결

      if (ec) {
        std::cerr << "Accept error: " << ec.message() << '\n';
        continue;
      }

      std::cout << "Client connected\n";

      // Client → Server

      char buffer[1024];
      // Client가 보낸 데이터를 저장할 공간

      std::size_t length = socket.read_some(boost::asio::buffer(buffer), ec);
      // Client가 데이터를 보낼 때까지 대기
      // 받은 데이터를 buffer에 저장
      // 실제 받은 바이트 수를 length에 저장

      if (ec) {
        std::cerr << "Read error: " << ec.message() << '\n';
        continue;
      }

      std::string received(buffer, length);

      std::cout << "Client: " << received << '\n';

      // Server → Client

      const std::string message = "Hello Client\n";

      boost::asio::write(socket, boost::asio::buffer(message), ec);
      // Server의 응답을 Client에게 전송

      if (ec) {
        std::cerr << "Write error: " << ec.message() << '\n';
        continue;
      }

      std::cout << "Response sent\n";
    }

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}