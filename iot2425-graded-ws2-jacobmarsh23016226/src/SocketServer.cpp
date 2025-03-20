#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws2-jacobmarsh23016226/src/SocketServer.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

// Constructor: Initializes the server with the specified UDP port
SocketServer::SocketServer(int udpPort) : port(udpPort) {}

// Starts the UDP socket server and listens for incoming messages
void SocketServer::start() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[1024];

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the specified port
    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Socket bind failed");
        std::cerr << "[ERROR] Failed to bind socket to port " << port << std::endl;
        close(sockfd);
        return;
    }
    std::cout << "[INFO] Server bound to port " << port << std::endl;

    std::cout << "Socket Server started on port " << port << ", waiting for messages..." << std::endl;

    // Main loop to receive and process messages
    while (true) {
        socklen_t len = sizeof(clientAddr);
        ssize_t received = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&clientAddr, &len);
        if (received > 0) {
            buffer[received] = '\0';  // Null-terminate received data
            char clientIp[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &clientAddr.sin_addr, clientIp, sizeof(clientIp));

            std::cout << "[DEBUG] Received from " << clientIp << ":" << ntohs(clientAddr.sin_port) 
                      << " -> " << buffer << std::endl;
            
            // Handle the message and send a response
            MessageHandler handler;
            handler.handleMessage(buffer, clientIp, ntohs(clientAddr.sin_port));
            handler.sendResponse(sockfd, "OK", clientAddr);
        }
    }

    close(sockfd);
}
