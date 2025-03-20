[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/287NU9li)
# TODO: overwrite this file with your solution to Activity 3

* Worksheet 1 Specification [here](https://xerte.uwe.ac.uk/USER-FILES/8660-me-perezhernandez-site/media/iot-2425-graded-worksheet-1.pdf)
* Check out markdown reference [here](https://www.markdownguide.org/basic-syntax/)

# Simulated GPS and eBikeClient - IoT Worksheet 1

- 23016226
- jacob marsh
- 2nd year cyber security and digtal forensics

## Overview
I developed a simulated GPS sensor that integrates with a Hardware Abstraction Layer (HAL). The `eBikeClient` application reads GPS data from a CSV file and prints formatted latitude and longitude values. Unit tests were implemented to verify functionality.

## Development Process

### **Generating Simulated GPS Data**
The `generateEBikeFile.cpp` utility was used to create a CSV file with GPS readings:

```sh
./generateEBikeFile 16226 1 5
```

This generated `data/sim-eBike-1.csv`, containing five latitude and longitude coordinate sets.

### **Implementing the GPS Sensor**
I implemented `GPSSensor.h` and `GPSSensor.cpp` to:
- Read GPS data from the CSV file.
- Format GPS data with a semicolon (`;`) separator.
- Process data sequentially.

### **Developing eBikeClient**
The `ebikeClient.cpp` program:
- Attaches the GPS sensor using `CSVHALManager`.
- Reads and displays GPS coordinates.
- Simulates time delays between readings.

Expected output:

```plaintext
[CSVHALManager] Device attached to port 0.
[GPS] 51.456180;-2.569593
[GPS] 51.456207;-2.569568
...
[CSVHALManager] Device released from port 0.
```

### **Unit Testing**
I used Catch2 for unit testing:

#### **GPSSensor Tests**
- Checked ID retrieval.
- Verified correct GPS data formatting.
- Ensured sequential data processing.

#### **eBikeClient Tests**
- Verified GPS sensor attachment and release.
- Checked correct GPS data retrieval and formatting.

### **Building and Running**
A `Makefile` was created for efficient compilation:

```sh
make
./generateEBikeFile 16226 1 5
./ebikeClient data/sim-eBike-1.csv 5
make test
```

## Challenges and solutions 

- **Parsing GPS Data Correctly in GPSSensor.cpp**  
  *Issue:* Initially, the logic to parse latitude and longitude from the CSV lines wasn’t robust. It failed when certain lines were blank or contained unexpected characters.  
  *Solution:* Added input validation checks and used more precise string handling to ensure only valid numerical values were read and converted.

- **Integrating with the HAL in eBikeClient.cpp**  
  *Issue:* When first calling `CSVHALManager`’s `attachDevice` method, it threw unexpected runtime errors due to incorrect port indexing.  
  *Solution:* Carefully reviewed the HAL documentation and adjusted the logic to use correct port numbers. Also added checks to ensure the device was only attached once before reading.

- **Formatting GPS Output Consistently in GPSSensor.cpp**  
  *Issue:* When constructing the formatted GPS string, early versions used incorrect delimiters or extra whitespace, making the output harder to parse.  
  *Solution:* Standardized the output format by ensuring a single semicolon separates latitude and longitude, with no trailing spaces. Updated tests to verify the format on every read.


## **Key Learnings**
- **HAL Integration:** Simulating hardware with `CSVHALManager`.
- **Unit Testing in C++:** Using Catch2 for validation.
- **File I/O in C++:** Structured reading from CSV files.

## **Future Improvements**
- Add support for more sensors.
- Simulate real-time GPS feeds.
- Improve error handling for missing/invalid data.
