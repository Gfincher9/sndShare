#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <sys/stat.h>
#include <fstream>
int port = { 0 };
void confFetch() { //Check config file for persistent settings
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
    //struct for filesize
    struct stat fileSizeBuf;
    stat(path, &fileSizeBuf);
    int fileSize = fileSizeBuf.st_size;
    //Struct for socket creation
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = inet_addr(ip);
    int clientSoc = socket(AF_INET, SOCK_STREAM, 0);

    //Connect Socket
    int sockSuccess = connect(clientSoc, (struct sockaddr*)&servAddr, sizeof(servAddr));
    if (sockSuccess != 0) { //if socket isn't found remotely... wait.
        std::cout << "Connection not found, waiting on open port..." << std::endl;
        while (sockSuccess != 0) {
        sockSuccess = connect(clientSoc, (struct sockaddr*)&servAddr, sizeof(servAddr));
        sleep(1);
    }
    }


    if (sockSuccess == 0) { //else begin
    FILE *fp = fopen(path, "r");
    //check if file exists
    if (fp == NULL) { 
        std::cout << "File not found";
    }

    else {
    fclose(fp);
    char buf[1024];
    std::ifstream file(path);
        for (int i = 0; i*1024 < fileSize; i++) {
            if (((i+1)*1024) > fileSize) {
                file.seekg((i*1024), std::ios::beg); 
                file.read(buf,(fileSize%1024));
                send(clientSoc, buf, (fileSize%1024), 0);
                for (int j = (fileSize%1024); j < 1024; j++) {
                    buf[j]='\0';
                }
                file.close();
            }
            else {
               file.seekg(i*1024, std::ios::beg);
               file.read(buf, 1024);
               send(clientSoc, buf, 1024, 0);
               std::fill_n(buf, 1024, '_');
            }
        }
        }
    close(clientSoc);
    std::cout << "Data delivered!" << std::endl;
    }
    }
    
int main(int argc, char* argv[]) {
    confFetch(); //Check snd.conf for config settings
    std::string path,ipA;
    //determine what to field for based on arg count 
    if (argc == 1) {
            std::cout << "Please enter the IP address which you wish to connect to" << std::endl;
            std::cin >> ipA;
            std::cout << "Please enter the path to the file which you wish to send" << std::endl;
            std::cin.ignore(); //clear out stdin
            std::getline(std::cin, path);
            
    }
    
    else if (argc == 2) { //doesn't work rn... :(
            ipA = argv[1];
            std::cout << "Please enter the path to the file which you wish to send" << std::endl;
            std::getline(std::cin, path);
}
        
        else {
            std::cout << "Invalid Argument count";
            return 1;
        }

        //begin driver func
    socketConnect(ipA.c_str(), path.c_str());
}