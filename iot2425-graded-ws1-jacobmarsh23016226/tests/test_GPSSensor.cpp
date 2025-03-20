#define CATCH_CONFIG_MAIN  // Define the main entry point for Catch2
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws1-jacobmarsh23016226/tests/catch.hpp"
#include "/home/jacob2.marsh/IoT-worksheet/iot2425-graded-ws1-jacobmarsh23016226/src/GPSSensor.h"

// Test that GPSSensor retrieves correct ID and can read at least one GPS coordinate
TEST_CASE("GPSSensor retrieves correct ID and dimension") {
    GPSSensor gps("data/sim-eBike-1.csv");
    REQUIRE(gps.getId() == 1);  // Assuming device ID is 1

    double lat, lon;
    REQUIRE(gps.readNext(lat, lon));  // Check if at least one GPS reading exists
}

// Test that GPSSensor correctly formats GPS data
TEST_CASE("GPSSensor correctly formats GPS data") {
    GPSSensor gps("data/sim-eBike-1.csv");

    double lat, lon;
    REQUIRE(gps.readNext(lat, lon));  // Ensure it reads a value
    std::string data = gps.getData();

    REQUIRE(data.find(";") != std::string::npos);  // Should contain a semicolon
    REQUIRE(data.length() > 5);  // Basic length check
}

// Test that GPSSensor handles multiple readings correctly
TEST_CASE("GPSSensor handles multiple readings") {
    GPSSensor gps("data/sim-eBike-1.csv");

    double lat, lon;
    int count = 0;
    
    // Loop through all available GPS readings
    while (gps.readNext(lat, lon)) {
        count++;
    }

    REQUIRE(count > 0);  // At least one reading should exist
    REQUIRE_FALSE(gps.hasMoreData());  // Should return false after consuming all data
}

