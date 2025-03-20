#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws2-jacobmarsh23016226/src/SocketServer.h"
#include <iostream>
#include <thread>
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws2-jacobmarsh23016226/src/WebServer.h"


int main() {
    // Initialize the UDP Socket Server for handling eBike location updates
    SocketServer socketServer(9783);

    // Initialize the Web Server to serve the eBike data and map interface
    WebServer webServer(9783);

    // Start the socket server in a separate thread to handle UDP data reception
    std::thread socketThread([&]() { socketServer.start(); });

    // Start the web server in a separate thread to handle HTTP requests
    std::thread webThread([&]() { webServer.start(); });

    std::cout << "[INFO] Web server started on http://localhost:9783" << std::endl;

    // Keep both servers running indefinitely
    socketThread.join();
    webThread.join();

    return 0;
}