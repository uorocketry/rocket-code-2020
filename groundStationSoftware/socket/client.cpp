// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#include <thread>
#include "chrono"
#define PORT 8080
   
int main(int argc, char const *argv[]) 
{ 
   
    
    while (1)
    {
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
        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
        { 
            printf("\nInvalid address/ Address not supported \n"); 
            continue;
        } 
        std::cout << "Try to connect\n";
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0) 
        { 
            char buffer[1] = {-1}; 
            // send(sock , hello , strlen(hello) , 0 ); 
            // printf("Hello message sent\n"); 
            bool connected = true;
            while(connected) 
            {
                std::cout << "Before " << (int)buffer[0] << " ";
                valread = read( sock , buffer, 1);
                // std::cout << valread << "\n";

                if(valread == 0) {
                    connected = false;
                } else {
                    std::cout << (int)buffer[0] << "\n"; 
                    // buffer[0] = -1;
                }
                std::this_thread::sleep_for(std::chrono::duration<int64_t, std::nano>(100000000));
            }
        } 
        
    }   

  
    return 0; 
} 