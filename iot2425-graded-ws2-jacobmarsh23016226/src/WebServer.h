#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class WebServer {
    public:
        // Constructor: Initializes the web server on the specified port
        explicit WebServer(int port) : port(port) {}
    
        // Starts the web server to handle incoming HTTP requests
        void start() {
            std::cout << "[INFO] Web server started on http://localhost:" << port << std::endl;
    
            int server_fd, new_socket;
            struct sockaddr_in address;
            int addrlen = sizeof(address);
    
            // Create a TCP socket
            server_fd = socket(AF_INET, SOCK_STREAM, 0);
            if (server_fd == 0) {
                perror("[ERROR] Socket creation failed");
                return;
            }
    
            // Configure socket settings
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons(port);
    
            // Bind socket to the specified port
            if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
                perror("[ERROR] Bind failed");
                return;
            }
    
            // Start listening for incoming connections
            if (listen(server_fd, 3) < 0) {
                perror("[ERROR] Listen failed");
                return;
            }
    
            std::cout << "[INFO] Web server listening on port " << port << std::endl;
    
            // Main loop to handle HTTP requests
            while (true) {
                new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
                if (new_socket < 0) {
                    perror("[ERROR] Accept failed");
                    continue;
                }
    
                // Read HTTP request
                char buffer[1024] = {0};
                read(new_socket, buffer, 1024);
                std::string request(buffer);
    
                // Check if request is for eBike data
                if (request.find("GET /ebikes") != std::string::npos) {
                    std::string jsonData = getEbikeData();
                    std::string response = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: " +
                                           std::to_string(jsonData.length()) + "\r\n\r\n" + jsonData;
                    send(new_socket, response.c_str(), response.size(), 0);
                } 
                // Serve static HTML file (map.html)
                else {
                    std::ifstream file("/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws2-jacobmarsh23016226/src/html/map.html");
                    std::stringstream buffer;
                    if (file) {
                        buffer << file.rdbuf();
                        file.close();
                    } else {
                        buffer << "<html><body><h1>Error: Could not load map.html</h1></body></html>";
                    }
    
                    std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " +
                                           std::to_string(buffer.str().size()) + "\r\n\r\n" + buffer.str();
                    send(new_socket, response.c_str(), response.size(), 0);
                }
    
                // Close client connection
                close(new_socket);
            }
        }
    
        // Updates eBike data with received GPS information
        static void updateEbikeData(const json& ebikeJson) {
            std::lock_guard<std::mutex> lock(dataMutex);  // Ensure thread safety
            ebikeData.push_back(ebikeJson);
        }
    
    private:
        int port;  // Port on which the server listens
    
        static inline std::vector<json> ebikeData; // Stores eBike location data
        static inline std::mutex dataMutex; // Mutex for thread-safe operations
    
        // Retrieves stored eBike data in JSON format
        static std::string getEbikeData() {
            std::lock_guard<std::mutex> lock(dataMutex);
            json response = {{"features", ebikeData}};
            return response.dump();
        }
    };
    
    #endif // WEBSERVER_H