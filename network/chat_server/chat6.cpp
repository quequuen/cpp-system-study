/*
TCP
│
├─ JSON인지 모름
├─ 메시지 경계도 모름
│
└─ 바이트를 순서대로 전달
         ↓
   우리가 프로토콜을 정의
         ↓
      프레이밍
         ↓
    메시지 하나 추출
         ↓
      JSON 파싱
         ↓
 sender / message / timestamp ...
         ↓
       UI에 표시 (현재 코드에서 UI는 미구현)

서버가 보내는 실제 데이터:
{"sender":"Client1","message":"hi"}\n
{"sender":"Client2","message":"hello"}\n

data framing:
TCP에서 받은 조각
      ↓
receive_buffer에 계속 붙임
      ↓
\n 찾기
      ↓
\n 이전까지 = 완성된 메시지
      ↓
JSON 파싱

통신 구조:
Client 1
   │
   │ "hello" 입력
   ↓
Server의 Session 1
   │
   │ run()
   ↓
socket.read_some()
   ↓
receive_buffer
   ↓
프레이밍
   ↓
JSON 파싱
   ↓
message = "hello"
   ↓
broadcast()
   │
   ├──────────────→ Session 2
   │                    │
   │                    ↓
   │                  send()
   │                    │
   │                    ↓
   │                 socket
   │                    │
   │                    ↓
   │                 Client 2
   │                    │
   │                    ↓
   │                화면에 표시
   │
   └──────────────→ Session 3
                        │
                        ↓
                      send()
                        │
                        ↓
                     Client 3
*/

#include <algorithm>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>  // json 사용
#include <string>
#include <thread>
#include <vector>

using boost::asio::ip::tcp;
using json = nlohmann::json;

// 전방 선언
class Session;

// 전역 Session 목록과 mutex
std::vector<std::shared_ptr<Session>> sessions;
std::mutex sessions_mutex;

// broadcast 전방 선언
void broadcast(const std::string& name, const std::string& message,
               std::shared_ptr<Session> sender);

// Session
class Session : public std::enable_shared_from_this<Session> {
 private:
  tcp::socket socket;
  std::string name;
  std::string receive_buffer;

 public:
  Session(tcp::socket socket, std::string name)
      : socket(std::move(socket)), name(std::move(name)) {}

  // 메시지를 이 Session의 Client에게 전송
  void send(const std::string& name, const std::string& message) {
    json data;

    data["sender"] = name;
    data["message"] = message;

    std::string formatted_message = data.dump() + "\n";

    boost::system::error_code ec;

    boost::asio::write(socket, boost::asio::buffer(formatted_message), ec);

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

      if (it != sessions.end()) {
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
  }

  // Client와 통신
  void run() {
    try {
      std::cout << name << " connected\n";

      for (;;) {
        char buffer[1024];

        boost::system::error_code ec;

        std::size_t length = socket.read_some(boost::asio::buffer(buffer), ec);

        if (ec == boost::asio::error::eof) {
          std::cout << name << " disconnected\n";
          break;
        }

        if (ec) {
          std::cerr << "Read error: " << ec.message() << '\n';
          break;
        }

        receive_buffer.append(buffer, length);

        // buffer에 들어온 프레이밍된 데이터 json으로 복구 후 broadcast
        while (true) {
          auto pos = receive_buffer.find('\n');

          if (pos == std::string::npos) {
            break;
          }

          std::string frame = receive_buffer.substr(0, pos);

          receive_buffer.erase(0, pos + 1);

          // frame = JSON 하나

          json data = json::parse(frame);

          std std::string message = data["message"];

          broadcast(name, message, shared_from_this());
        }
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
void broadcast(const std::string& name, const std::string& message,
               std::shared_ptr<Session> sender) {
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
    session->send(name, message);
  }
}

int main() {
  try {
    boost::asio::io_context io_context;

    tcp::endpoint endpoint(tcp::v4(), 13);

    tcp::acceptor acceptor(io_context, endpoint);

    std::cout << "Server started\n";

    int client_number = 1;

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
      auto session = std::make_shared<Session>(
          std::move(socket), "Client" + std::to_string(client_number++));

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