## `Boost.Asio`

### Boost.Asio를 사용하는 이유

    C++에서 네트워크 동신과 비동기 I/O를 구현할 수 있도록 제공하는 라이브러리. 중요한 점은 `Boost.Asio`가 TCP나 UDP 자체를 대체하는 건 아님. TCP와 UDP는 여전히 동일하고, `Boost.Asio`는 그 기능을 C++에서 사용하기 편리하게 제공하는 것.

### 주요 개념

- `io_context`

  ```cpp
  boost::asio::io_context io;
  ```

  `Boost.Asio`의 I/O 실행 환경. 동기식 코드에서는 주로 소켓 등의 객체를 생성할 때 사용하고, 비동기식 코드에서는 완료 핸들러를 실행하는 이벤트 처리의 중심이 됨.

- `udp::endpoint`

  ```cpp
  using boost::asio::ip::udp;

  udp::endpoint server(
      boost::asio::ip::make_address("127.0.0.1"),
      9000
  );
  ```

  통신 상대방의 IP 주소와 포트를 나타내는 객체. `POSIX`의 `sockaddr_in`과 비슷한 역할.

- `udp_socket`

  ```cpp
  udp::socket socket(io);
  socket.open(udp::v4());
  ```

  UDP 소켓을 관리하는 객체. `POSIX`의 `int client_socket`과 대응시켜 생각하면 됨. 다만 단순한 정수와 달리 객체가 소켓 자원의 수명과 관련된 기능도 제공함.
