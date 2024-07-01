CXX = g++
CXXFLAGS = -std=c++11 -Wall
INCLUDES = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lboost_system -lpthread

TARGET = server
SRC_DIR = src
BUILD_DIR = build
SRCS = $(SRC_DIR)/server.cpp

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SRCS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $@ $(LDFLAGS) $(LIBS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

.PHONY: all clean run
