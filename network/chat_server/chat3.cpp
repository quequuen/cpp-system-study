#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

using boost::asio::ip::tcp;

class Session {
 private:
  tcp::socket socket;

 public:
  // 생성될 때 Client와 연결된 socket을 받음
  Session(tcp::socket socket) : socket(std::move(socket)) {}

  // Client와 통신
  void run() {
    try {
      std::cout << "Client connected\n";

      for (;;) {
        char buffer[1024];

        boost::system::error_code ec;

        // Client → Server
        std::size_t length = socket.read_some(boost::asio::buffer(buffer), ec);

        // Client가 정상적으로 연결 종료
        if (ec == boost::asio::error::eof) {
          std::cout << "Client disconnected\n";
          break;
        }

        if (ec) {
          std::cerr << "Read error: " << ec.message() << '\n';
          break;
        }

        std::string message(buffer, length);

        std::cout << "Client: " << message;

        // Server → Client
        const std::string response = "Server received: " + message;

        boost::asio::write(socket, boost::asio::buffer(response), ec);

        if (ec) {
          std::cerr << "Write error: " << ec.message() << '\n';
          break;
        }
      }

    } catch (const std::exception& e) {
      std::cerr << "Session error: " << e.what() << '\n';
    }
  }
};

int main() {
  try {
    boost::asio::io_context io_context;

    tcp::endpoint endpoint(tcp::v4(), 13);

    tcp::acceptor acceptor(io_context, endpoint);

    std::cout << "Server started\n";

    for (;;) {
      std::cout << "Waiting for client...\n";

      tcp::socket socket(io_context);

      boost::system::error_code ec;

      acceptor.accept(socket, ec);

      if (ec) {
        std::cerr << "Accept error: " << ec.message() << '\n';
        continue;
      }
      // 기본적인 세션 생성
      // 연결된 socket으로 Session 생성

      // Session session(std::move(socket));

      // "Read error: Bad file descriptor..."가 뜨는 이유
      // 해당 코드는 Session이 지역 변수이기 때문에 detach() 이후에 죽어버림
      // detach()로 인해 Thread는 살아있지만 세션은 먼저 죽었기 때문에 연결 유지
      // 불가능 그래서 shared_ptr이 필요

      // Session을 별도의 Thread에서 실행
      // std::thread client_thread(&Session::run, &session);

      auto session = std::make_shared<Session>(std::move(socket));
      // make_shared()로 인해 main의 지역변수 session이 사라져도 Thread의 작업을
      // 끝낼 때까지 Session이 살아있을 수 있음.

      std::thread client_thread(&Session::run, session);
      // 위처럼 &session을 하게 되면 shared_ptr의 주소(포인터)가 되어버리기
      // 때문에 &를 떼어야 함. Session::run()은 Session 객체에서 실행되어야 하기
      // 때문
      // &session이 아닌 Session 객체 자체를 원하는 것

      client_thread.detach();
    }

  } catch (const std::exception& e) {
    std::cerr << "Server error: " << e.what() << '\n';
  }
}