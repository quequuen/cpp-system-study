/*
                 Server
                   │
          sessions │
                   │
       ┌───────────┼───────────┐
       ↓           ↓           ↓
   Session A   Session B   Session C
       │           │           │
    socket A    socket B    socket C
       │           │           │
    Client A    Client B    Client C
*/

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using boost::asio::ip::tcp;

// Session 미리 선언 → sessions의 제네릭에 사용
class Session;
// broadcast 미리 선언 → class Seesion의 run 메소드 내 사용
void broadcast(const std::string& message, std::shared_ptr<Session> sender);

std::vector<std::shared_ptr<Session>> sessions;
std::mutex sessions_mutex;

// Session
class Session : public std::enable_shared_from_this<Session> {
 private:
  tcp::socket socket;

 public:
  Session(tcp::socket socket) : socket(std::move(socket)) {}

  // 메시지를 이 Session의 Client에게 전송
  void send(const std::string& message) {
    boost::system::error_code ec;

    boost::asio::write(socket, boost::asio::buffer(message), ec);

    if (ec) {
      std::cerr << "Write error: " << ec.message() << '\n';
    }
  }

  // Client와 통신
  void run() {
    try {
      std::cout << "Client connected\n";

      for (;;) {
        char buffer[1024];

        boost::system::error_code ec;

        std::size_t length = socket.read_some(boost::asio::buffer(buffer), ec);

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

        // 나를 제외한 모든 Client에게 전송
        broadcast(message, shared_from_this());
      }

    } catch (const std::exception& e) {
      std::cerr << "Session error: " << e.what() << '\n';
    }
  }
};

// Broadcast
void broadcast(const std::string& message, std::shared_ptr<Session> sender) {
  // sessions를 읽는 동안 다른 Thread가 수정하지 못하도록 잠금
  std::lock_guard<std::mutex> lock(sessions_mutex);

  for (auto& session : sessions) {
    // 메시지를 보낸 Client는 제외
    if (session != sender) {
      session->send(message);
    }
  }
}

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

      // 새로운 Session 생성
      auto session = std::make_shared<Session>(std::move(socket));

      // Server의 Session 목록에 추가
      {
        std::lock_guard<std::mutex> lock(sessions_mutex);

        sessions.push_back(session);
      }

      // Session을 별도의 Thread에서 실행
      std::thread client_thread(&Session::run, session);

      client_thread.detach();
    }

  } catch (const std::exception& e) {
    std::cerr << "Server error: " << e.what() << '\n';
  }
}