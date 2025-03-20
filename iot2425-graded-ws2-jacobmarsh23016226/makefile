CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -Iinclude -pthread
SRC_DIR = src
UTIL_DIR = src/util
BUILD_DIR = build
BIN_DIR = bin
TEST_DIR = tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(UTIL_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

EXEC = $(BIN_DIR)/ebikeClient $(BIN_DIR)/generateEBikeFile $(BIN_DIR)/ebikeGateway
TEST_EXEC = $(BIN_DIR)/test_GPSSensor $(BIN_DIR)/test_ebikeClient

all: $(EXEC)

# Build ebikeClient
$(BIN_DIR)/ebikeClient: $(BUILD_DIR)/ebikeClient.o $(BUILD_DIR)/GPSSensor.o
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Build generateEBikeFile
$(BIN_DIR)/generateEBikeFile: $(BUILD_DIR)/generateEBikeFile.o
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Build ebikeGateway (Added Gateway)
$(BIN_DIR)/ebikeGateway: $(BUILD_DIR)/ebikeGateway.o $(BUILD_DIR)/SocketServer.o $(BUILD_DIR)/MessageHandler.o
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -pthread

# Compile GPSSensor
$(BUILD_DIR)/GPSSensor.o: $(SRC_DIR)/GPSSensor.cpp $(SRC_DIR)/GPSSensor.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile ebikeClient
$(BUILD_DIR)/ebikeClient.o: $(SRC_DIR)/ebikeClient.cpp $(SRC_DIR)/GPSSensor.h $(SRC_DIR)/hal/CSVHALManager.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile ebikeGateway
$(BUILD_DIR)/ebikeGateway.o: $(SRC_DIR)/ebikeGateway.cpp $(SRC_DIR)/SocketServer.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile SocketServer
$(BUILD_DIR)/SocketServer.o: $(SRC_DIR)/SocketServer.cpp $(SRC_DIR)/SocketServer.h $(SRC_DIR)/MessageHandler.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile MessageHandler
$(BUILD_DIR)/MessageHandler.o: $(SRC_DIR)/MessageHandler.cpp $(SRC_DIR)/MessageHandler.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile generateEBikeFile
$(BUILD_DIR)/generateEBikeFile.o: $(UTIL_DIR)/generateEBikeFile.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile other source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Unit Tests
test: $(TEST_EXEC)

$(BIN_DIR)/test_GPSSensor: $(TEST_DIR)/test_GPSSensor.o $(BUILD_DIR)/GPSSensor.o
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/test_ebikeClient: $(TEST_DIR)/test_ebikeClient.o
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
