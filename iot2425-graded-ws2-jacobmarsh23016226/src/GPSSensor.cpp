#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws2-jacobmarsh23016226/src/GPSSensor.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor: Loads GPS data from a file
GPSSensor::GPSSensor(const std::string& filename) : index(0), deviceId(1) {
    file.open(filename);
    if (!file) {
        std::cerr << "Error: Could not open GPS data file: " << filename << std::endl;
        return;
    }

    double lat, lon;
    char comma;
    while (file >> lat >> comma >> lon) {
        coordinates.emplace_back(lat, lon);
    }
    file.close();
    std::cout << "[DEBUG] Loaded " << coordinates.size() << " GPS records from file." << std::endl;
}

// Reads the next GPS coordinate, returns false if no data remains
bool GPSSensor::readNext(double& lat, double& lon) {
    if (index >= coordinates.size()) {
        std::cerr << "[ERROR] No more GPS data to read!" << std::endl;
        return false;
    }
    
    lat = coordinates[index].first;
    lon = coordinates[index].second;
    std::cout << "[DEBUG] GPS Read: " << lat << ", " << lon << std::endl;
    
    index++;
    return true;
}

// Returns the unique device ID
int GPSSensor::getId() const {
    return deviceId;
}

// Checks if there is more GPS data to read
bool GPSSensor::hasMoreData() const {
    return index < coordinates.size();
}
