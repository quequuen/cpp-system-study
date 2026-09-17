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


Client 연결 종료
      ↓
read_some()에서 EOF 또는 오류 발생
      ↓
run()의 반복문 탈출
      ↓
disconnect() 호출
      ↓
sessions에서 자기 자신 제거
      ↓
socket 종료
      ↓
Session 정리
*/

#include <algorithm>  // std::find()
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using boost::asio::ip::tcp;

// 전방 선언
class Session;

// 전역 Session 목록과 mutex
std::vector<std::shared_ptr<Session>> sessions;
std::mutex sessions_mutex;

// broadcast 전방 선언
void broadcast(const std::string& message, std::shared_ptr<Session> sender);

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

  // 연결 종료 처리
  void disconnect() {
    // 현재 Session을 shared_ptr로 확보
    auto self = shared_from_this();

    {
      // sessions에 접근하므로 mutex 잠금
      std::lock_guard<std::mutex> lock(sessions_mutex);

      // sessions에서 현재 Session과 같은 객체를 찾음
      auto it = std::find(sessions.begin(), sessions.end(), self);
      // 반환 받은 it은 '해당 객체의 위치'
      // std::find()는 sessions 안에서 self를 찾고, 찾았다면 그 위치를 가리키는
      // iterator를 반환 하지만 찾지 못했다면 sessions.end() → sessions의 마지막
      // 원소가 아닌 마지막 원소의 다음 위치를 반환

      // 찾았다면 sessions에서 제거
      if (it != sessions.end()) {
        // sessions.end() → 마지막 원소의 다음 위치 → 만약 원소를 찾지 못했다면
        // sessions에서 해당 session을 제거
        sessions.erase(it);
      }  // 여기서 lock_guard 자동 unlock

      // 소켓 종료
      boost::system::error_code ec;

      socket.shutdown(tcp::socket::shutdown_both, ec);

      socket.close(ec);

      if (ec) {
        std::cerr << "Socket close error: " << ec.message() << '\n';
      }

      std::cout << "Session disconnected\n";
    }

    // Client와 통신
    void run() {
      try {
        std::cout << "Client connected\n";

        for (;;) {
          char buffer[1024];

          boost::system::error_code ec;

          std::size_t length =
              socket.read_some(boost::asio::buffer(buffer), ec);

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

      // 정상 종료든 오류 종료든
      // run()이 끝나면 연결 종료 처리
      disconnect();
    }
  };

  // Broadcast
  void broadcast(const std::string& message, std::shared_ptr<Session> sender) {
    std::vector<std::shared_ptr<Session>> targets;

    {
      // sessions를 읽는 동안 다른 Thread가 수정하지 못하도록 잠금
      std::lock_guard<std::mutex> lock(sessions_mutex);

      for (auto& session : sessions) {
        // 메시지를 보낸 Session은 제외
        if (session != sender) {
          targets.push_back(session);
        }
      }
    }  // 여기서 mutex 자동 해제

    // mutex를 잡지 않은 상태에서 네트워크 전송
    for (auto& session : targets) {
      session->send(message);
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
        }  // 여기서 mutex 자동 해제

        // Session을 별도 Thread에서 실행
        std::thread client_thread(&Session::run, session);

        client_thread.detach();
      }

    } catch (const std::exception& e) {
      std::cerr << "Server error: " << e.what() << '\n';
    }
  }