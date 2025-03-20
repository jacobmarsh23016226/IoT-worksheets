#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws2-jacobmarsh23016226/src/hal/CSVHALManager.h"
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws2-jacobmarsh23016226/src/GPSSensor.h"

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    // Validate command-line arguments
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <server_ip> <ebike_id> <csv_file> <num_readings>" << std::endl;
        return 1;
    }

    // Extract input parameters
    std::string serverIp = argv[1];  // eBike Gateway IP
    std::string eBikeId = argv[2];   // Unique eBike identifier
    std::string filename = argv[3];  // GPS data file (.csv)
    int numReadings = std::stoi(argv[4]); // Number of readings to send

    // Create UDP socket
    int sockfd;
    struct sockaddr_in serverAddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Failed to create socket");
        return 1;
    }
    
    // Enable address reuse
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // Configure server address (Gateway IP and Port)
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9783);
    inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr);

    // Initialize GPS sensor
    CSVHALManager halManager(1);
    std::shared_ptr<GPSSensor> gpsSensor = std::make_shared<GPSSensor>(filename);

    if (!gpsSensor->hasMoreData()) {
        std::cerr << "No data available from GPS sensor." << std::endl;
        return 1;
    }

    halManager.attachDevice(0, gpsSensor);

    // Send GPS data at regular intervals
    for (int i = 0; i < numReadings && gpsSensor->hasMoreData(); ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulate time delay
    
        double lat, lon;
        if (gpsSensor->readNext(lat, lon)) {
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            
            // Create JSON message with GPS data
            json gpsData = {
                {"id", eBikeId},
                {"timestamp", now},
                {"latitude", lat},
                {"longitude", lon},
                {"status", "Active"}
            };

            // Send data to the server
            std::string message = gpsData.dump();
            sendto(sockfd, message.c_str(), message.length(), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        }
    }

    // Clean up
    halManager.releaseDevice(0);
    close(sockfd);
    return 0;
}
