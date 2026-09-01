## 네트워크 (network)

### 네트워크 계층 모델

인터넷 통신을 여러 계픙으로 나누어 각 계층이 서로 다른 역할을 담당하도록 구성되어 있음.

- OSI 7계층과 TCP/IP 4계층

```
OSI 7계층                TCP/IP 4계층

Application ─┐
Presentation ├────────→ Application
Session ─────┘

Transport ────────────→ Transport

Network ──────────────→ Internet

Data Link ──┐
Physical ───┴─────────→ Network Access
```

- OSI는 개념적으로 세분화한 모델, TCP/IP 4계층은 실제 인터넷 프로토콜 스택을 설명할 때 더 실용적인 모델.

1. APPlication Layer
   애플리케이션이 사용하는 네트워크 프로토콜. `HTTP`, `HTTPS`, `DNS`, `FTP`, `SSH` 등. 예를 들어 `Chat Server`를 만든다면 애플리케이션 계층에서 '채팅 메시지의 형식' 같은 것을 정의하게 됨.

2. Transport Layer
   프로세스 간 통신을 담당하며 `Port`, `TCP`, `UDP`의 기능이 이 계층에서 수행됨.

3. Internet Layer
   IP의 영역. 대표적으로 `IPv4`, `IPv6`가 존재하고 패킷을 목적지 IP까지 전달하기 위한 논리적인 주소 지정과 라우팅을 수행. `192.168.0.10`, `127.0.0.1`, `IPv4`, `IPv6`, `Public IP`, `Private IP`와 같은 내용들이 이 계층과 연결.

4. Network Access Layer
   가장 최하층. 실제 네트워크를 통해 데이터를 전달하는 부분. `Ethernet`, `Wi-Fi`, `Mac Address`, `Ethernet Frame` 같은 개념들이 이곳에 해당.

```
┌──────────────────────────────┐
│ Application Layer            │
│                              │
│ HTTP / Chat Protocol / JSON  │
└──────────────┬───────────────┘
               │
               ▼
┌──────────────────────────────┐
│ Transport Layer              │
│                              │
│ TCP / UDP                    │
│ Port                         │
└──────────────┬───────────────┘
               │
               ▼
┌──────────────────────────────┐
│ Internet Layer               │
│                              │
│ IP (IPv4 / IPv6)             │
└──────────────┬───────────────┘
               │
               ▼
┌──────────────────────────────┐
│ Network Access Layer         │
│                              │
│ Ethernet / Wi-Fi             │
└──────────────────────────────┘
```

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

IPv4는 32 bit 주소라서 사용할 수 있는 주소가 약 43억 개. 처음에는 충분했지만 인터넷에 연결되는 장치가 폭발적으로 증가하면서 부족 현상으로 새로 만들어진 것이 IPv6. 128 bit를 사용하고 `2001:db8:85a3::8a2e:370:7334` 같은 형태.

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

```
Application
     │
     │ Socket API
     ▼
Operating System
     │
     ▼
TCP / UDP
     │
     ▼
IP
     │
     ▼
Ethernet / Wi-Fi
```

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
  - 데이터를 보내기 전에 양쪽 사이에 연결을 설정함.
    ```
    Client                    Server
    │                         │
    │ ────── 연결 설정 ───────→ │
    │                         │
    │ ←──── 연결 설정 완료 ───── │
    │                         │
    │ ←────── TCP 연결 ──────→ │
    ```
  - 위의 연결 설정 과정이 바로 **3-way Handshake**. UDP는 이런 연결 설정 과정 없이 데이터를 바로 보낼 수 있다는 점에서 차이가 있음.
  - 3-way Handshake

    ```
    Client                      Server

    SYN ───────────────────────→

        ←──────────────── SYN + ACK

    ACK ───────────────────────→

            연결 성립
    ```

    - SYN: 클라이언트 측에서 서버랑 TCP 연결을 요청.
    - SYN + ACK: 서버 측에서 요청에 대한 가능 여부를 알려줌.
    - ACK: 클라이언트 측에서 확인했다는 것을 응답.
      이 과정을 거치면 TCP 연결 성립.

- 신뢰성 (Reliable)
  - 데이터를 보낼 때 상대방에게 제대로 전달됐는지 확인하고, 필요한 경우 재전송하는 메커니즘을 가지고 있음. 그렇기 때문에 애플리케이션 입장에서는 네트워크에서 패킷 유실 여부같은 세세한 부분을 직접 관리할 필요가 줄어들음. → 이상이 있다면 재전송을 하기 때문.
- 순서 보장 (Ordered)
  - 데이터가 순서대로 전달되도록 보장함. 네트워크에서는 데이터의 실제 전달 순서가 보낸 순서와 다를 수 있음. TCP는 이를 적절히 처리해서 애플리케이션에서 순서를 기존처럼 재구성해 데이터를 제공함. → 그래서 파일 전송이나 HTTP 같은 곳에서 유용.
- Byte Stream
  - 메시지 단위(패킷 단위)가 아닌 연속된 **Byte Stream**으로 데이터 전달. 예를 들어 클라이언트가 `"Hello"`라는 데이터를 한 번에 보냈다고 해서 서버가 반드시 `read()` → `"Hello"`를 한 번에 받는다고 보장되지 않음. `read()` → `"Hel"`, `read()` → `"llo"` 이렇게 무작위적으로 데이터가 전달될 수 있음.
  - `Message Boundary`를 보장하지 않음. → Chat Server를 만들 때 굉장히 중요함.
    - TCP는

      ```
      Message 1
      Message 2
      Message 3
      ```

      과 같은 개념을 알지 못하고

      ```
      "Message 1Message 2Message 3"
      ```

      이라는 연속된 바이트 스트림일 뿐임. 그래서 애플리케이션이 메시지 경계를 직접 정의 해야 함.
      - `\n`을 구분자로 사용.

        ```
        Hello\n
        How are you?\n
        Bye\n
        ```

      - 길이를 앞에 붙임.

        ```
        [5][Hello]
        [12][How are you?]
        ```

        이러한 방식을 `Message Framing`이라고 함.

- Flow Control
  - 송신자가 수신자가 처리할 수 있는 속도보다 너무 빠르게 데이터를 보내지 않도록 조절하는 기능. 예를 들어 Client가 엄청 빠르게 보내는데 Server가 느릴 경우, 수신자의 버퍼 상태 등을 기반으로 전송량을 조절. 수신자를 기준으로 조절. Reciever를 보호하기 위해 제어.
- Congestion Control
  - 네트워크 자체의 혼잡을 기준으로 조절. 네트워크를 보호하기 위해 제어.

- 데이터 전달 방법
  TCP가 다루는 것은 **Byte Stream**. 예를 들어 `01001000 01100101 01101100 01101100 01101111` 같은 바이트들의 연속. TCP는 이걸 안정적으로 전달해주는 역할을 해. 그 위에서 HTTP, JSON, Chat Message, File 같은 의미를 만들어내는 것.

- 장점
  - 신뢰성 있는 데이터 전달
  - 순서 보장
  - Flow Control
  - Congestion Control
  - 네트워크 세부 사항을 애플리케이션이 직접 처리할 필요 감소

- 단점
  - 연결 관리 및 제어로 인한 오버헤드
  - UDP에 비해 상대적으로 높은 지연 가능성
  - Byte Stream이므로 Message Framing을 애플리케이션에서 구현해야 함.

### TCP 서버 구조

- `socket`: 통신에 사용할 Socket 생성.
- `bind`: Socket에 IP Address + Port 할당.
- `listen`: Client의 연결 요청을 받을 수 있는 상태로 전환.
- `accept`: 연결 요청을 받아 새로운 통신용 Socket 생성.
- `read`/`recv`: Client가 보낸 데이터 수신.
- `write`/`send`: Client에게 데이터 전송.
- `close`: 연결 종료.

| TCP Server 개념    | Boost.Asio                              |
| ------------------ | --------------------------------------- |
| `socket()`         | `tcp::socket`                           |
| `bind()`           | `tcp::acceptor` 생성 과정에서 처리 가능 |
| `listen()`         | `tcp::acceptor`가 처리                  |
| `accept()`         | `acceptor.accept()`                     |
| `read()`/`recv()`  | `socket.read_some()` 등                 |
| `write()`/`send()` | `socket.write_some()`/`asio::write()`   |
| `close()`          | `socket.close()`                        |

- `socket()`
  가장 먼저 네트워크 통신에 사용할 Socket을 생성. 일반적인 BSD Socket API에서는

  ```cpp
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  ```

  - `AF_INET`: IPv4
  - `SOCK_STREAM`: TCP
  - `0`: 프로토콜 자동 선택
    즉, IPv4 TCP 통신을 할 수 있는 Socket을 하나 만든다는 의미. 해당 부분에서는 아직 특정 Port에서 Client를 기다리는 상태가 아님. 단순히 통신에 사용할 Socket이라는 자원을 만든 것.

- `bind()`
  Socket을 생성 후, 어떤 주소에서 통신할 것인지 지정함.

  ```cpp
  bind(server_fd, ...);
  ```

  개념적으로는 `Socket` + `IP Address` + `Port` + `bind()`. 해당 Socket을 이 IP와 Port에서 사용하겠다는 의미. 즉, `bind()`는 Socket과 주소를 연결하는 과정. 예를 들어 `127.0.0.1:8080`에 연결.

- `listen()`
  `bind()`에서 서버가 특정 주소를 사용하도록 했지만 아직 Client 연결을 받는 상태가 아님. 해당 함수로 Socket을 Client의 TCP 연결 요청을 기다리는 Listening Socket으로 만들어줌.

  ```cpp
  listen(server_fd, SOMAXCONN);
  ```

  해당 함수로 인해 Client 연결 요청을 기다리는 상태가 됨.
