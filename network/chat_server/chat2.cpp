// TCP Chat Server - 여러 Client
//
// Server
//   ├── Client A → Thread A
//   ├── Client B → Thread B
//   └── Client C → Thread C
//
// 각 Client를 별도의 Thread에서 처리하기 때문에
// 한 Client가 통신하는 동안 다른 Client도 동시에 처리할 수 있음.

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>

using boost::asio::ip::tcp;

// 하나의 Client를 처리하는 함수
void handle_client(tcp::socket socket) {
  try {
    std::cout << "Client connected\n";

    for (;;) {
      // Client가 보낸 데이터를 저장할 공간
      char buffer[1024];

      boost::system::error_code ec;

      // Client → Server

      std::size_t length = socket.read_some(boost::asio::buffer(buffer), ec);

      // 연결이 정상적으로 종료된 경우
      if (ec == boost::asio::error::eof) {
        std::cout << "Client disconnected\n";
        break;
      }

      // 그 외의 오류
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
    std::cerr << "Client error: " << e.what() << '\n';
  }
}

int main() {
  try {
    boost::asio::io_context io_context;

    // IPv4 + 13번 Port
    tcp::endpoint endpoint(tcp::v4(), 13);

    // Client 연결을 기다리는 acceptor
    tcp::acceptor acceptor(io_context, endpoint);

    std::cout << "Server started\n";

    for (;;) {
      // 새로운 Client와 통신할 Socket
      tcp::socket socket(io_context);

      std::cout << "Waiting for client...\n";

      boost::system::error_code ec;

      // Client 연결을 기다림
      acceptor.accept(socket, ec);

      if (ec) {
        std::cerr << "Accept error: " << ec.message() << '\n';
        continue;
      }

      // Socket을 새로운 Thread로 이동
      std::thread client_thread(handle_client, std::move(socket));

      // Thread를 독립적으로 실행
      client_thread.detach();
    }

  } catch (const std::exception& e) {
    std::cerr << "Server error: " << e.what() << '\n';
  }
}