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
  sockaddr_in server_address{};

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(9000);

  // 주소와 socket 연결
  if (bind(server_socket, reinterpret_cast<sockaddr*>(&server_address),
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