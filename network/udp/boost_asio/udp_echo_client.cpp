
#include <array>
#include <boost/asio.hpp>
#include <iostream>
#include <string>

namespace asio = boost::asio;
using asio::ip::udp;

int main() {
  try {
    asio::io_context io;

    // IPv4 UDP 소켓 생성
    udp::socket socket(io, udp::v4());

    // 서버 주소
    udp::endpoint server_endpoint(asio::ip::make_address("127.0.0.1"), 9000);

    std::string message;

    std::cout << "Message (exit to quit): ";

    while (std::getline(std::cin, message)) {
      if (message == "exit") {
        break;
      }

      // 서버로 데이터 전송
      socket.send_to(asio::buffer(message), server_endpoint);

      // 서버의 응답 수신
      std::array<char, 1024> buffer{};
      udp::endpoint sender_endpoint;

      std::size_t length =
          socket.receive_from(asio::buffer(buffer), sender_endpoint);

      std::cout << "Server: " << std::string(buffer.data(), length) << '\n';

      std::cout << "Message (exit to quit): ";
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
}
