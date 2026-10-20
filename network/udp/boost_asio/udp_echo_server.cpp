
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

    // 서버의 포트 9000에 바인딩
    udp::endpoint server_endpoint(asio::ip::address_v4::any(), 9000);
    socket.bind(server_endpoint);

    std::cout << "UDP Echo Server started on port 9000\n";

    while (true) {
      std::array<char, 1024> buffer{};
      udp::endpoint client_endpoint;

      // 클라이언트의 데이터 수신
      std::size_t length =
          socket.receive_from(asio::buffer(buffer), client_endpoint);

      std::string message(buffer.data(), length);

      std::cout << "Client: " << message << '\n';

      // 수신한 클라이언트에게 그대로 응답
      socket.send_to(asio::buffer(buffer.data(), length), client_endpoint);
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
}
