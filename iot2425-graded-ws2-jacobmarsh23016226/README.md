[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/R5HJg_0V)

* Worksheet 2 Specification [here](https://xerte.uwe.ac.uk/USER-FILES/8660-me-perezhernandez-site/media/iot-2425-graded-worksheet-2.pdf)
* Check out markdown reference [here](https://www.markdownguide.org/basic-syntax/)

# eBike Location Tracking System - IoT worksheet 2

- 23016226
- jacob marsh
- 2nd year cyber security and digtal forensics

## Development Process

1. **Understanding Requirements**  
   - Reviewed the worksheet instructions and analyzed the provided codebase.
   - Identified key components needing modification: `ebikeClient.cpp`, `ebikeGateway.cpp`, `SocketServer.h/cpp`, `MessageHandler.h/cpp`, `GPSSensor.h/cpp`, and `WebServer.h/cpp`.

2. **Setting Up UDP Communication**  
   - Implemented `SocketServer` to handle UDP messages.
   - Updated `ebikeClient.cpp` to send GPS data in JSON format.
   - Used `recvfrom()` in `SocketServer` to receive and process messages.

3. **GPS Data Handling**  
   - Modified `GPSSensor` to read and format GPS data.
   - Structured data in JSON format, including latitude, longitude, timestamp, and ID.

4. **Processing and Storing Data**  
   - Created `MessageHandler` to parse incoming messages.
   - Converted GPS data to GeoJSON format and stored it in `WebServer`.

5. **Web Server Implementation**  
   - Developed `WebServer` to serve eBike location data.
   - Enabled dynamic map updates to display eBikes using GeoJSON.

6. **Testing and Debugging**  
   - Ran multiple `ebikeClient` instances with simulated GPS data.
   - Verified UDP communication and JSON parsing.
   - Ensured web server correctly displayed eBike locations.

## Challenges and Solutions

1. **UDP Message Loss**  
   - Added acknowledgment messages from the server to ensure delivery.

2. **JSON Parsing Errors**  
   - Implemented error handling in `MessageHandler` to catch malformed data.

3. **Multi-threading Issues**  
   - Used `std::mutex` to synchronize data access in `WebServer`.

4. **Network Communication Debugging**  
   - Used debug logs to track message flow between client and server.

## Key Learnings

- **UDP Communication**: Learned how to implement real-time data transmission over UDP.
- **JSON Handling**: Gained experience formatting and parsing JSON for IoT applications.
- **Multi-threading**: Applied threading techniques to run socket and web servers concurrently.
- **Web Integration**: Integrated backend data with a web-based map for real-time tracking.

This project provided hands-on experience in IoT, networking, and web development.
