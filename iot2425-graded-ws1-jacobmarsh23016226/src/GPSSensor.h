#ifndef GPSSENSOR_H
#define GPSSENSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws1-jacobmarsh23016226/src/hal/IDevice.h"  // Include the IDevice interface

// GPSSensor class represents a GPS device that inherits from IDevice
class GPSSensor : public IDevice {  
private:
    std::ifstream file;  // File stream for reading GPS data
    std::string sensorID;  // Sensor identifier
    std::vector<std::pair<double, double>> coordinates;  // Stores GPS coordinates
    size_t index;  // Tracks the current position in the data
    int deviceId;  // Unique device ID

public:
    // Constructor: Loads GPS data from a file
    GPSSensor(const std::string& filename) : sensorID("GPS-001"), index(0), deviceId(1) {  
        file.open(filename);
        if (!file) {
            std::cerr << "Error: Could not open GPS data file." << std::endl;
            return;
        }
        double lat, lon;
        char comma;
        while (file >> lat >> comma >> lon) {
            coordinates.emplace_back(lat, lon);
        }
        file.close();
    }

    // Reads the next GPS coordinate and updates lat/lon
    bool readNext(double& lat, double& lon) {
        if (index >= coordinates.size()) return false;
        lat = coordinates[index].first;
        lon = coordinates[index].second;
        index++;
        return true;
    }

    // Returns the device ID
    int getId() const override {  
        return deviceId;
    }

    // Retrieves the current GPS data as a formatted string
    std::string getData() {
        if (index >= coordinates.size()) return "End of Data";
        double lat = coordinates[index].first;
        double lon = coordinates[index].second;
        index++;
        return std::to_string(lat) + "; " + std::to_string(lon);
    }

    // Checks if more GPS data is available
    bool hasMoreData() const {
        return index < coordinates.size();
    }
};

#endif // GPSSENSOR_H
