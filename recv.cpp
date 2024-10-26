#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
void socketConnect(const char* ip) {
    int servSoc=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8080);
    servAddr.sin_addr.s_addr = inet_addr(ip);
    bind(servSoc, (struct sockaddr*)&servAddr, sizeof(servAddr));
    listen(servSoc, 5);
    int clientSoc=accept(servSoc, nullptr, nullptr);
    char buff[1024] = { 0 };
    recv(clientSoc, buff, sizeof(buff), 0);
std::cout << buff <<  std::endl;
close(servSoc);
}
int main() {
    socketConnect("10.0.2.15");
}