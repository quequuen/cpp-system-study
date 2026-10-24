## `Boost.Asio`

### Boost.Asio를 사용하는 이유

    C++에서 네트워크 동신과 비동기 I/O를 구현할 수 있도록 제공하는 라이브러리. 중요한 점은 `Boost.Asio`가 TCP나 UDP 자체를 대체하는 건 아님. TCP와 UDP는 여전히 동일하고, `Boost.Asio`는 그 기능을 C++에서 사용하기 편리하게 제공하는 것.

### 핵심 객체

- `io_context`

  ```cpp
  boost::asio::io_context io;
  ```

  `Boost.Asio`의 I/O 실행 환경. 동기식 코드에서는 주로 소켓 등의 객체를 생성할 때 사용하고, 비동기식 코드에서는 완료 핸들러를 실행하는 이벤트 처리의 중심이 됨.

- `endpoint`

  ```cpp
  using boost::asio::ip::udp;

  udp::endpoint server(
      boost::asio::ip::make_address("127.0.0.1"),
      9000
  );
  ```

  통신 상대방의 IP 주소와 포트를 나타내는 객체. `POSIX`의 `sockaddr_in`과 비슷한 역할.

- `socket`

  ```cpp
  udp::socket socket(io);
  socket.open(udp::v4());
  ```

  네트워크 데이터를 보내고 받는 데 사용하는 객체. `POSIX`의 `int client_socket`과 대응시켜 생각하면 됨. 다만 단순한 정수와 달리 객체가 소켓 자원의 수명과 관련된 기능도 제공함.

- `acceptor`

```cpp
namespace asio = boost::asio;
using asio::ip::tcp;

asio::io_context io;

tcp::acceptor acceptor(
    io,
    tcp::endpoint(tcp::v4(), 9000)
);

tcp::socket socket(io);

acceptor.accept(socket);
```

여기서부터는 TCP와 UDP를 구분해야 함. TCP에서는 클라이언트가 서버에 연결을 요청하고, 서버가 그 요청을 받아들여 통신을 시작함. 이때 서버가 연결 요청을 기다리고 받아들이는 역할을 하는 객체.

```
1. tcp::acceptor
서버 포트에서 연결 요청 대기
        ↓
2. acceptor.accept(socket)
연결 요청을 받아 통신용 소켓에 연결
        ↓
3. tcp::socket
연결된 클라이언트와 데이터 송수신
```

UDP는 TCP처럼 연결 요청을 받아들이는 과정이 없기 때문에 `acceptor`가 없음.

| 개념       | TCP                         | UDP                      |
| ---------- | --------------------------- | ------------------------ |
| `endpoint` | 주소와 포트                 | 주소와 포트              |
| `socket`   | 연결된 상대와 데이터 송수신 | 데이터그램 송수신        |
| `acceptor` | 연결 요청을 기다리고 수락   | 일반적으로 사용하지 않음 |

```cpp
// UDP
udp::endpoint server(address, port);
udp::socket socket(io, udp::v4());
socket.send_to(asio::buffer(message), server);

// TCP
tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 9000));
tcp::socket socket(io);
acceptor.accept(socket);
```

### 동기식 I/O

- 동기식 I/O의 의미 (Synchronous I/O)
  동기식 I/O는 I/O 작업의 결과를 기다린 후 다음 작업을 진행하는 방식. 함수가 호출되면 작업이 완료되거나 오류가 발생할 때까지 해당 호출 흐름이 기다릴 수 있음.
  - 블로킹(Blocking): 데이터 수신처럼 작업이 완료될 때까지 호출한 스레드가 대기할 수 있음.

  - 순차적 실행: 앞선 작업이 끝난 뒤 다음 코드를 실행하므로 실행 흐름을 이해하기 쉬움.

  - 단점: 응답을 기다리는 동안 해당 스레드는 다른 작업을 수행하지 못할 수 있음.

  ```cpp
  std::array<char, 1024> buffer{};
  udp::endpoint sender;

  std::size_t length = socket.receive_from(
      asio::buffer(buffer),
      sender
  );

  // 데이터 수신이 완료된 뒤 실행됨
  std::cout << "Received: "
          << std::string(buffer.data(), length)
          << '\n';
  ```

  `receive_from()`은 수신할 데이터가 도착하거나 오류가 발생할 때까지 기다릴 수 있음. 따라서 데이터 수신이 완료된 뒤 다음 코드가 실행됨.

  비동기식 I/O와의 차이: 동기식은 호출한 흐름에서 작업 결과를 기다리는 반면, 비동기식은 작업을 요청한 뒤 완료 핸들러 등을 통해 결과를 처리할 수 있음.

- UDP 데이터 송수신
  - `send_to()` - UDP 데이터 전송
    `send_to()`는 지정한 목적지의 IP 주소와 포트로 UDP 데이터그램을 전송하는 함수.

    ```cpp
    std::string message = "Hello";

    udp::endpoint server_endpoint(
        asio::ip::make_address("127.0.0.1"),
        9000
    );

    socket.send_to(
        asio::buffer(message),
        server_endpoint
    );
    ```

    - `asio::buffer(message)`: 전송할 데이터가 저장된 메모리를 나타내는 버퍼.
    - `server_endpoint`: 데이터를 보낼 목적지의 IP 주소와 포트.

    ```
    1. message에 전송할 데이터를 저장.
    2. asio::buffer()로 해당 데이터의 메모리를 Asio가 사용할 수 있도록 나타냄. → 예를 들어 프로그램 메모리 상에 'H, e, l, l, o'라는 데이터가 저장되어 있을 때, 이 데이터를 UDP로 보내고 싶으면 socket.send_to()는 어디에 있는 데이터를 보낼지, 데이터가 몇 바이트인지를 알아야 함. 그리고 asio.::buffer()는 메모리를 가리키는 정보를 만들어 주는 역할을 함. 여기서 asio::buffer(message)는 문자열을 새로 복사해서 만드는 게 아닌, 기존 문자열의 데이터에 접근할 수 있도록 시작 위치와 크기 같은 정보를 제공함.
    3. send_to()가 지정된 목적지로 데이터그램을 전송함.
    ```

    여기서 `asio::buffer()`는 데이터를 복사하거나 소유하는 객체가 아님. 기존 메모리를 가리키는 뷰를 제공함. 또한 `send_to`가 성공적으로 반환됐다고 해서 상대방이 데이터를 실제로 받았다는 뜻이 아님. UDP는 데이터 전달을 보장하지 않기 때문.

- `receive_from()`
- TCP 데이터 송수신
  - `connect()`
  - `accept()`
  - `read_some()`
  - `write()`
- `asio::buffer()`의 역할
- POSIX 소켓 API와 Boost.Asio 비교

```

```
