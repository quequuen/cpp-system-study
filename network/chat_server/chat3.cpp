#include <boost/asio.hpp>
#include <iostream>
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

      // 연결된 socket으로 Session 생성
      Session session(std::move(socket));

      // Session을 별도의 Thread에서 실행
      std::thread client_thread(&Session::run, &session);

      client_thread.detach();
    }

  } catch (const std::exception& e) {
    std::cerr << "Server error: " << e.what() << '\n';
  }
}