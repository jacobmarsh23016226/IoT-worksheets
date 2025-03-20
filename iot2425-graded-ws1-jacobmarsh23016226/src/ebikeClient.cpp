#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws1-jacobmarsh23016226/src/hal/CSVHALManager.h"
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws1-jacobmarsh23016226/src/GPSSensor.h"

int main(int argc, char* argv[]) {
    // Ensure correct usage of the program
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <csv_file> <num_readings>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];  // GPS data file path
    int numReadings = std::stoi(argv[2]);  // Number of readings to process

    CSVHALManager halManager(1);  // Initialize HAL manager with 1 port

    // Create a shared pointer to the GPS sensor device
    std::shared_ptr<IDevice> gpsSensor = std::make_shared<GPSSensor>(filename);

    // Ensure there is available data before proceeding
    if (std::dynamic_pointer_cast<GPSSensor>(gpsSensor)->hasMoreData() == false) {
        std::cerr << "No data available from GPS sensor." << std::endl;
        return 1;
    }

    // Attach the GPS sensor to the HAL manager
    halManager.attachDevice(0, gpsSensor);

    // Process GPS readings
    for (int i = 0; i < numReadings && std::dynamic_pointer_cast<GPSSensor>(gpsSensor)->hasMoreData(); ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulate time delay between readings

        double lat, lon;
        bool success = std::dynamic_pointer_cast<GPSSensor>(gpsSensor)->readNext(lat, lon);
        if (success) {
            std::cout << "[" << i+1 << "] GPS: " << lat << "; " << lon << std::endl;
        } else {
            std::cerr << "Error reading GPS data." << std::endl;
        }
    }

    // Release the GPS sensor from the HAL manager
    halManager.releaseDevice(0);

    return 0;
}
