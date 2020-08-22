#ifndef TESTING

#include "IO.h"
#include "../data/SBGData.h"
#include <iostream>
#include"SocketClient.h"
#include "chrono"
#include <thread>

SocketClient::SocketClient() {

}

SocketClient::~SocketClient() {

}

void SocketClient::run() {
    while (true) {
        // std::cout << "running client\n";
        // std::this_thread::sleep_for(std::chrono::duration<int64_t, std::nano>(1000000000));
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
