#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws2-jacobmarsh23016226/src/MessageHandler.h"

// UDP socket server for handling incoming messages
class SocketServer {
    private:
        int port; // Server's listening port
    
    public:
        explicit SocketServer(int udpPort); // Initializes the server with a port
        void start(); // Starts the server and listens for messages
    };
    
    #endif // SOCKETSERVER_H