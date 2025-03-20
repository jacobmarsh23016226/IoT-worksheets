#define CATCH_CONFIG_MAIN  // Define the main entry point for Catch2
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws1-jacobmarsh23016226/tests/catch.hpp"
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws1-jacobmarsh23016226/src/GPSSensor.h"
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws1-jacobmarsh23016226/src/hal/CSVHALManager.h"

// Test that eBikeClient can correctly attach and release a GPS sensor
TEST_CASE("eBikeClient attaches and releases GPS sensor correctly") {
    CSVHALManager halManager(1);  // Initialize HAL manager with 1 port
    std::shared_ptr<GPSSensor> gpsSensor = std::make_shared<GPSSensor>("data/sim-eBike-1.csv");

    REQUIRE_NOTHROW(halManager.attachDevice(0, gpsSensor));  // Ensure no exception is thrown when attaching
    REQUIRE_NOTHROW(halManager.releaseDevice(0));  // Ensure no exception is thrown when releasing
}

// Test that eBikeClient correctly reads GPS data from the sensor
TEST_CASE("eBikeClient reads GPS data correctly") {
    CSVHALManager halManager(1);
    std::shared_ptr<GPSSensor> gpsSensor = std::make_shared<GPSSensor>("data/sim-eBike-1.csv");

    halManager.attachDevice(0, gpsSensor);  // Attach the GPS sensor

    double lat, lon;
    REQUIRE(gpsSensor->readNext(lat, lon));  // Ensure that at least one GPS reading can be retrieved

    std::string data = gpsSensor->getData();
    REQUIRE(data.find(";") != std::string::npos);  // Check that the data format contains a semicolon

    halManager.releaseDevice(0);  // Release the GPS sensor
}
