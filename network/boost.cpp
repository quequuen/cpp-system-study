#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

int main() {
  try {
    boost::asio::io_context io_context;

    tcp::endpoint endpoint(tcp::v4(), 13);
    tcp::acceptor acceptor(io_context, endpoint);

    std::cout << "Server started\n";

    for (;;) {
      tcp::socket socket(io_context);

      std::cout << "Waiting for client...\n";

      boost::system::error_code ec;
      acceptor.accept(socket, ec);

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