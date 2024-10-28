#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
int port = { 0 };
void confFetch() {
    char buf[11];
    char newbuf[5];
    FILE *fp = fopen("snd.conf", "r");
    //todo: add config file if uncreated
    fgets(buf, 11, fp);
    fclose(fp);
    for (int i = 5; i < strlen(buf); i++) {
        newbuf[i-5] = buf[i];
    } 
    port = std::stoi(newbuf);
}
void socketConnect(const char* ip, const char* path) {
sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
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
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        std::cout << "File not found";
    }
    else {
    char *buf;
    while (fgets(buf, 1024, fp)!=NULL) {
     send(clientSoc, buf, strlen(buf), 0);
    }
     fclose(fp);
     close(clientSoc);
     std::cout << "Data delivered!" << std::endl;
    }
    }
    
}
int main(int argc, char* argv[]) {
    confFetch();
    std::string path,ipA;
    if (argc == 1) {
            std::cout << "Please enter the IP address which you wish to connect to" << std::endl;
            std::cin >> ipA;
            std::cout << "Please enter the path to the file which you wish to send" << std::endl;
            std::cin.ignore();
            std::getline(std::cin, path);
            
    }
    else if (argc == 2) {
            ipA = argv[1];
            std::cout << "Please enter the path to the file which you wish to send" << std::endl;
            std::getline(std::cin, path);
}
        else {
            std::cout << "Invalid Argument count";
            return 1;
        }
    socketConnect(ipA.c_str(), path.c_str());
}