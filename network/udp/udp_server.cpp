#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

int main() {
  // UDP socket 생성
  int server_socket = socket(AF_INET, SOCK_DGRAM, 0);

  if (server_socket == -1) {
    std::cerr << "socket() failed\n";
    return 1;
  }

  // 서버 주소 설정
  sockaddr_in server_address{};  // IPv4 주소 정보를 담는 구조체

  server_address.sin_family = AF_INET;  // IPv4 주소 체계 사용, AF_INET6 = IPv6
  server_address.sin_addr.s_addr = INADDR_ANY;
  // 서버가 특정 IP 하나에만 묶이지 않고, 사용가능한 모든 로컬
  // IPv4 인터페이스의 주소에서 요청을 받도록 하겠다는 의미
  // 컴퓨터 한 대는 여러 IP주소를 가지고 있을 수 있음. 예를 들어, Wi-Fi로
  // 네트워크에 연결하는 IP, Ethernet 케이블로 연결하는 IP, 127.0.0.1이라는 자기
  // 자신을 가리키는 루프백 주소. INADDR_ANY로 하면 밑에 설정한 포트 번호에서
  // 로컬 IPv4 인터페이스의 주소를 대상으로 수신하도록 소켓을 설정.
  // INADDR_ANY는 정확하게 말하자면 소켓 주소 설정에 사용하는 특별한 상수.
  // 클라이언트의 접속 주소로 쓰는 게 아닌, 서버가 어디에서 수신할지 설정할 때
  // 사용한다고 보면 됨.
  server_address.sin_port = htons(9000);
  // 서버가 사용할 포트 번호를 9000으로 설정

  // 주소와 socket 연결
  if (bind(server_socket, reinterpret_cast<sockaddr*>(&server_address),
           // reinterpret_cast: 서로 다른 타입의 포인터를 다른 타입으로 변환할
           // 때 사용하는 형변환 연산자
           // 구조체의 실제 데이터가 다른 구조체로 변환되는 게 아님
           // server_address{} 객체는 여전히 sockaddr_in 타입.
           // reinterpret_cast는 객체 자체를 새로 만들거나 데이터를 복사지 않음.
           // 여기서는 그 객체를 가리키는 포인터의 타입을 바꾸는 것.

           sizeof(server_address)) == -1) {
    std::cerr << "bind() failed\n";
    close(server_socket);
    return 1;
  }

  std::cout << "UDP Echo Server started\n";

  for (;;) {
    char buffer[1024];

    // 클라이언트 주소
    sockaddr_in client_address{};
    socklen_t client_address_length = sizeof(client_address);

    // 데이터그램 수신
    ssize_t length = recvfrom(server_socket, buffer, sizeof(buffer) - 1, 0,
                              reinterpret_cast<sockaddr*>(&client_address),
                              &client_address_length);

    if (length == -1) {
      std::cerr << "recvfrom() failed\n";
      break;
    }

    buffer[length] = '\0';

    std::cout << "Client: " << buffer << '\n';

    // 받은 데이터그램을 그대로 다시 전송
    sendto(server_socket, buffer, length, 0,
           reinterpret_cast<sockaddr*>(&client_address), client_address_length);
  }

  close(server_socket);
}