#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws2-jacobmarsh23016226/src/MessageHandler.h"
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws2-jacobmarsh23016226/src/WebServer.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <chrono>

using json = nlohmann::json;

// Convert time_t to a formatted string (YYYY-MM-DD HH:MM:SS)
std::string formatTimestamp(time_t rawTime) {
    std::ostringstream oss;
    std::tm* timeInfo = std::localtime(&rawTime);
    oss << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// Handles incoming messages, processes GPS data, and updates eBike records
void MessageHandler::handleMessage(const char* message, const char* clientIp, uint16_t clientPort) {
    try {
        json receivedJson = json::parse(message);
        time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        // Format GPS data as GeoJSON
        json geoJson = {
            {"geometry", {
                {"type", "Point"},
                {"coordinates", {receivedJson["longitude"], receivedJson["latitude"]}}
            }},
            {"type", "Feature"},
            {"properties", {
                {"id", receivedJson["id"]},
                {"timestamp", formatTimestamp(now)}, // Human-readable timestamp
                {"status", "Active"}
            }}
        };

        // Store updated data in the WebServer
        WebServer::updateEbikeData(geoJson);
    } catch (const json::exception& e) {
        std::cerr << "[ERROR] JSON parsing failed: " << e.what() << std::endl;
    }
}

// Sends a response message to the client
void MessageHandler::sendResponse(int sockfd, const char* response, struct sockaddr_in& clientAddr) {
    sendto(sockfd, response, strlen(response), 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
    std::cout << "[DEBUG] Sent response: " << response << std::endl;
}
