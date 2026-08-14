#include <boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

int main() {
  try {
    boost::asio::io_context io_context;

    std::cout << "Boost.Asio is working!\n";
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}