#ifndef GPSSENSOR_H
#define GPSSENSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws2-jacobmarsh23016226/src/hal/IDevice.h"

class GPSSensor : public IDevice {
    private:
        std::ifstream file;  // File stream for reading GPS data
        std::vector<std::pair<double, double>> coordinates; // Stores GPS coordinates
        size_t index; // Current reading position
        int deviceId; // Unique device identifier
    
    public:
        GPSSensor(const std::string& filename); // Loads GPS data from file
        bool readNext(double& lat, double& lon); // Reads the next GPS coordinate
        int getId() const override; // Returns the device ID
        bool hasMoreData() const; // Checks if more data is available
    };
    
    #endif // GPSSENSOR_H