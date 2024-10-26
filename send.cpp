#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
void socketConnect(const char* ip, const char* msg) {
sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8080);
    servAddr.sin_addr.s_addr = inet_addr(ip);
    int clientSoc = socket(AF_INET, SOCK_STREAM, 0);
    connect(clientSoc, (struct sockaddr*)&servAddr, sizeof(servAddr));
    send(clientSoc, msg, strlen(msg), 0);
    close(clientSoc);
}
int main() {
    socketConnect("10.0.2.15", "Kys loser");
}