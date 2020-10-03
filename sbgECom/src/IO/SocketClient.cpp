#ifndef TESTING

#include "SocketClient.h"
#include "../data/SBGData.h"
#include "IO.h"
#include "../helpers/Types.h"

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#include <chrono>
#include <thread>
#include <queue>

#define PORT 8080
#define HOST_IP "127.0.0.1"
#define RECONNECT_WAIT_TIME_NS duration_ns(1000000000) // 1 second
#define UPDATE_WAIT_TIME_NS duration_ns(10000000) // 100th of a second

SocketClient::SocketClient() {

}

SocketClient::~SocketClient() {

}

void SocketClient::run() {
    while (true) {
        std::this_thread::sleep_for(RECONNECT_WAIT_TIME_NS);
        int sock = 0, valread; 
        struct sockaddr_in serv_addr;
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
            std::cout << "Socket creation error" << "\n"; 
            continue;
        } 
    
        serv_addr.sin_family = AF_INET; 
        serv_addr.sin_port = htons(PORT); 
        
        // Convert IPv4 and IPv6 addresses from text to binary form 
        if(inet_pton(AF_INET, HOST_IP, &serv_addr.sin_addr) <= 0) { 
            std::cout << "Invalid address / Address not supported" << "\n"; 
            continue;
        } 

        std::cout << "Trying to connect..." << "\n";
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0) { 
            std::cout << "Connected\n";
            char buffer[1] = {(char)-1}; 
            bool connected = true;
            while (connected) {
                valread = read( sock , buffer, 1);

                if (valread == 0) {
                    connected = false;
                    close(sock);
                } 

                eventNumberQueue.push((int)buffer[0]);
        
                std::this_thread::sleep_for(UPDATE_WAIT_TIME_NS);
            }
        } 
    }

}

void SocketClient::initialize(){
    std::cout << "initialize client thread" << "\n";
    IO::initialize();

};

int SocketClient::getData() {
    std::lock_guard<std::mutex> lockGuard(mutex);

    if(eventNumberQueue.empty()) {
        return -1;
    }

    int nbr = eventNumberQueue.front();
    eventNumberQueue.pop();
    return nbr;
}

#endif
