#ifndef TESTING

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include "IO.h"
#include "../data/SBGData.h"
#include <iostream>
#include"SocketClient.h"
#include "chrono"
#include <thread>

#define PORT 8080



SocketClient::SocketClient() {

}

SocketClient::~SocketClient() {

}

void SocketClient::run() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::duration<int64_t, std::nano>(1000000000));
        int sock = 0, valread; 
        struct sockaddr_in serv_addr;
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        { 
            printf("\n Socket creation error \n"); 
            continue;
        } 
    
        serv_addr.sin_family = AF_INET; 
        serv_addr.sin_port = htons(PORT); 
        
        // Convert IPv4 and IPv6 addresses from text to binary form 
        if(inet_pton(AF_INET, "192.168.1.1", &serv_addr.sin_addr)<=0)  
        { 
            printf("\nInvalid address/ Address not supported \n"); 
            continue;
        } 
        std::cout << "Trying to connect...\n";
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0) 
        { 
            std::cout << "Connected\n";
            char buffer[1] = {(char)-1}; 
            bool connected = true;
            while(connected) 
            {
                valread = read( sock , buffer, 1);

                if(valread == 0) {
                    connected = false;
                    close(sock);
                } 

                std::cout << (int)buffer[0] << "\n";
                buffer[0] = (char)-1;

                std::this_thread::sleep_for(std::chrono::duration<int64_t, std::nano>(100000000));
            }
        } 
    }

}

void SocketClient::initialize(){
    std::cout << "initialize client thread";
    IO::initialize();

};

int SocketClient::getData() {
    return -1;
}

#endif
