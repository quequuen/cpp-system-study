## 네트워크 (network)

### Client / Server

- Client (클라이언트)
  네트워크를 통해 Server에 서비스를 요청하고, 그 결과를 받는 프로그램 또는 장치. 예를 들면 웹 브라우저, 모바일 앱, 게임 클라이언트 등.
- Server (서버)
  Client의 요청을 받아 처리하고, 그 결과를 제공하는 프로그램 또는 컴퓨터. 요청을 받아 서비스를 제공하는 역할을 하는 프로그램. Server는 여러 Client의 연결을 받아 서비스를 제공할 수 있음.

|             | Client                    | Server                  |
| ----------- | ------------------------- | ----------------------- |
| 역할        | 서비스 요청               | 서비스 제공             |
| 요청과 응답 | 요청을 보내고 응답을 받음 | 요청을 받고 응답을 보냄 |
| 예시        | 브라우저, 앱              | 웹 서버, 게임 서버      |

- 보통 Client 측에서 요청을 하지만 연결이 맺어진 직후에는 양쪽 모두 데이터를 보낼 수 있음. 특히 TCP 채팅에서는 `Client ↔ Server`처럼 양방향 통신을 함.

- 통신 흐름

```
 Client
    ↓ Request
 Server
    ↓ Response
 Client
```

### IP Address

네트워크에서 장치를 식별하고, 데이터가 어느 네트워크 주소로 전달되어야 하는지를 나타내는 주소. 쉽게 말하면 네트워크에서 데이터를 어디로 보내야 하는가를 나타내는 주소. 예를 들어, `Client`가 `Server`에 요청을 할 때 어느 Server인지를 알아야 하니 IP Address를 이용해 목적지를 지정하는 방식.

```
Client
   ↓ 192.168.0.10
Server
```

하지만 `192.168.0.10`이라는 컴퓨터에 프로그램이 여러 개 실행되고 있다면 어느 프로그램으로 가야 하는지 혼란이 옴. → 그래서 `Port`가 필요함.

```
IP Address + Port
       ↓
192.168.0.10:8080
```

- IPv4

```
32 bits
 ↓
8 bits + 8 bits + 8 bits + 8 bits
 ↓
192 . 168 . 0 . 10
```

각각의 숫자는 8비트이므로 `0 ~ 255`의 범위를 가질 수 있음. `0.0.0.0 ~ 255.255.255.255`

- IPv6

IPv4는 32 bit 주소라서 사용할 수 있는 주소가 약 43억 개. 처음에는 충분했지만 인터넷에 연결되는 장치가 폭발적으로 증가하면서 부족 현상으로 새로 만들어진 것이 IPv6. 129 bit를 사용하고 `2001:db8:85a3::8a2e:370:7334` 같은 형태.

|           | IPv4           | IPv6          |
| --------- | -------------- | ------------- |
| 주소 크기 | 32비트         | 128비트       |
| 표현      | `192.168.0.10` | `2001:db8::1` |
| 주소 개수 | 약 43억        | 매우 많음     |

- 공인 IP (Public IP)
  인터넷에서 다른 네트워크와 통신할 때 사용되는 주소. 인터넷에서 특정 네트워크/장치를 식별하는 데 사용.

- 사설 IP (Private IP)
  내부 네트워크에서 사용하는 IP. 인터넷 전체에서 고유한 주소가 아닌 공유기 같은 장치가 외부 네트워크와 연결.

- loopback 주소
  `127.0.0.1`과 같은 '내 컴퓨터 자신'을 가리키는 주소. `localhost`가 이 주소를 가리키며 IPv6에서는 `::1`.

### Port

하나의 컴퓨터에서 네트워크 통신의 목적기인 프로세스/서비스를 구분하기 위한 16비트 번호.

- 범위
  - 0 ~ 65535
  - 0 ~ 1023: Well-known Port
  - 1024 ~ 49151: Registered Port
  - 49152 ~ 65535: Dynamic / Private Port

- IP와의 관계
  - IP: 어느 컴퓨터/네트워크 인터페이스인가
  - Port: 그 컴퓨터에서 어느 네트워크 서비스인가

- Server
  - 특정 Port를 열고 Client의 연결을 기다림.
  - 예: HTTP → 80, HTTPS → 443

- Client
  - 연결할 때 운영체제가 임시 Port를 할당하는 경우가 일반적.

- TCP 연결
  - Source IP
  - Source Port
  - Destination IP
  - Destination Port

### Socket

Socket은 애플리케이션이 네트워크를 통해 데이터를 주고받을 수 있도록 운영체제가 제공하는 통신 인터페이스. 프로그램이 직접 이더넷이나 TCP 패킷을 조작하는 게 아니라 **Socket을 통해 운영체제에 네트워크 통신을 요청하는 것.**
Socket은 TCP 전용 개념이 아님. TCP, UDP 둘 다 사용 가능.

- IP + Port: 통신 대상(endpoint)
- Socket: 그 대상과 통신하기 위한 인터페이스.

- TCP Socket
  TCP에서는 연결을 기반으로 통신.

  ```
  Client                         Server

  Socket                         Socket
  │                              │
  │─────── TCP Connection ───────│
  │                              │
  │──────────── Data ───────────→│
  │←─────────── Data ────────────│
  │                              │
  ```

  TCP에서는 Socket을 통해 `connect`, `read`, `write`, `close` 같은 작업을 수행함.
  - TCP 기본 흐름

    ```cpp
    #include <boost/asio.hpp>
    #include <iostream>
    #include <string>

    using boost::asio::ip::tcp;

    int main() {
    try {
        boost::asio::io_context io_context;

        tcp::endpoint endpoint(tcp::v4(), 13);
        // endpoint 생성
        // IPv4 + Port 13
        // 127.0.0.1:13 같은 네트워크 주소 정보

        tcp::acceptor acceptor(io_context, endpoint);
        // acceptor 생성
        // Server가 해당 주소에서 Client 연결을 받을 준비

        std::cout << "Server started\n";

        for (;;) {
        tcp::socket socket(io_context);
        // 통신을 위한 Socket 객체 준비

        std::cout << "Waiting for client...\n";

        boost::system::error_code ec;
        acceptor.accept(socket, ec);
        // Client가 접속할 때까지 기다림

        if (ec) {
            std::cerr << "Accept error: " << ec.message() << '\n';
            continue;
        }
        // 에러 발생 시 에러 메시지 출력

        std::cout << "Client connected\n";
        // 클라이언트 접속 성공
        // socket에 연결이 성립

        const std::string message = "Hello From Server\n";

        boost::asio::write(socket, boost::asio::buffer(message), ec);
        // 해당 Client에게 데이터 전송

        if (ec) {
            std::cerr << "Write error: " << ec.message() << '\n';
        }

        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    }
    ```

    - TCP Server의 기본 흐름: `socket` → `bind` → `listen` → `accept` → `read / write` → `close`
    - `acceptor`: Client의 연결 요청을 받아들이는 역할
    - `socket`: 연결된 Client와 실제 데이터를 주고받는 역할
    - TCP Client의 기본 흐름: `socket` → `connect` → `read / write` → `close`

- UDP Socket
  UDP는 연결을 유지하는 방식이 아님. 데이터를 보낼 때 목적지 주소를 함께 지정해서 보내는 방식.

  ```
  Client Socket
      │
      │ Datagram
      ▼
  Server Socket
  ```

  UDP에서는 대표적으로 `send_to`, `receive_from` 같은 작업을 수행.

TCP Socket은 TCP 연결을 통해 데이터를 송수신하고, UDP Socket은 Datagram으로 송수신함.

### TCP (Transmission Control Protocol)

두 호스트 간에 신뢰성 있고 순서가 보장되는 Byte Stream 통신을 제공하는 연결 지향형 전송 계층 프로토콜.

네트워크에서는 데이터를 보내면 끝이 나는 게 아님. 인터넷을 거치면서 패킷 유실, 패킷 순서 변경, 중복, 전송 지연 등 다양한 문제가 발생할 수 있음. TCP는 이런 문제를 애플리케이션이 직접 처리하지 않아도 되도록 여러 기능을 제공함.

- 연결 지향 (Connection-oriented)
  - 데이터를 주고받기 전에 연결을 설정
  - 3-way Handshake
- 신뢰성 (Reliable)
  - 데이터 전달을 확인
  - 필요한 경우 재전송
- 순서 보장 (Ordered)
  - 데이터가 순서대로 전달되도록 보장
- Byte Stream
  - 메시지 단위가 아닌 연속된 Byte Stream으로 데이터 전달
  - Message Boundary를 보장하지 않음
  - 애플리케이션에서 Message Framing 필요
- Flow Control
  - 수신자가 처리할 수 있는 양을 고려하여 전송 속도 조절
- Congestion Control
  - 네트워크 혼잡 상태에 따라 전송 속도 조절
