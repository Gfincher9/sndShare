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
    int sockSuccess = connect(clientSoc, (struct sockaddr*)&servAddr, sizeof(servAddr));
    if (sockSuccess != 0) {
        std::cout << "Connection not found, waiting on open port..." << std::endl;
        while (sockSuccess != 0) {
        sockSuccess = connect(clientSoc, (struct sockaddr*)&servAddr, sizeof(servAddr));
        sleep(1);
    }
    }
    if (sockSuccess == 0) {
     send(clientSoc, msg, strlen(msg), 0);
     close(clientSoc);
     std::cout << "Message delivered!";
    }
    
}
int main(int argc, char* argv[]) {
    std::string msg,ipA;
    if (argc < 2) {
            std::cout << "Please enter the IP address which you wish to connect to" << std::endl;
            std::cin >> ipA;
            std::cout << "Please enter the message which you wish to send" << std::endl;
            std::cin.ignore();
            std::getline(std::cin, msg);
            
    }
    else if (argc<3) {
            ipA = argv[1];
            std::cout << "Please enter the message which you wish to send" << std::endl;
            std::getline(std::cin, msg);
}
        else {
            ipA=argv[1];
            msg=argv[2];
        }
    socketConnect(ipA.c_str(), msg.c_str());
}