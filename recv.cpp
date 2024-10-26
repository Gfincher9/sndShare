#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <cstring>
int port = { 0 };
void confFetch() {
    char buf[11];
    char newbuf[5];
    FILE *fp = fopen("snd.conf", "r");
    fgets(buf, 11, fp);
    fclose(fp);
    for (int i = 5; i < strlen(buf); i++) {
        newbuf[i-5] = buf[i];
    } 
    port = std::stoi(newbuf);
}
void socketConnect(const char* ip) {
    int servSoc=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = inet_addr(ip);
    bind(servSoc, (struct sockaddr*)&servAddr, sizeof(servAddr));
    listen(servSoc, 0);
    int clientSoc=accept(servSoc, nullptr, nullptr);
    char buff[2048] = { 0 };
    recv(clientSoc, buff, sizeof(buff), 0);
    std::cout << buff <<  std::endl;
close(servSoc);
}
int main(int argc, char* argv[]) {
    confFetch();
    std::string ipA;
    if (argc < 2) {
        std::cout << "Please enter the IP address which you wish to connect to" << std::endl;
        std::cin >> ipA;
    }
    else {
        ipA=argv[1];
    }
    std::cout << "Listening for a message from " << ipA << std::endl;
    socketConnect(ipA.c_str());
}