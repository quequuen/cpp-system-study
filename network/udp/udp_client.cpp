#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

int main() {
  // UDP socket 생성
  int client_socket = socket(AF_INET, SOCK_DGRAM, 0);

  if (client_socket == -1) {
    std::cerr << "socket() failed\n";
    return 1;
  }

  // 서버 주소 설정
  sockaddr_in server_address{};

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9000);

  inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

  std::string message;

  std::cout << "Message: ";
  std::getline(std::cin, message);

  // 서버로 데이터그램 전송
  sendto(client_socket, message.data(), message.size(), 0,
         reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address));

  // 서버의 응답 수신
  char buffer[1024];

  sockaddr_in from_address{};
  socklen_t from_address_length = sizeof(from_address);

  ssize_t length = recvfrom(client_socket, buffer, sizeof(buffer) - 1, 0,
                            reinterpret_cast<sockaddr*>(&from_address),
                            &from_address_length);

  if (length == -1) {
    std::cerr << "recvfrom() failed\n";
    close(client_socket);
    return 1;
  }

  buffer[length] = '\0';

  std::cout << "Server: " << buffer << '\n';

  close(client_socket);
}