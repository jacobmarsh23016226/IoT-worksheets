#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <netinet/in.h>

// Handles incoming messages and updates eBike data
class MessageHandler {
    public:
        void handleMessage(const char* message, const char* clientIp, uint16_t clientPort);
        void sendResponse(int sockfd, const char* response, struct sockaddr_in& clientAddr);
    };
    
    #endif // MESSAGEHANDLER_H