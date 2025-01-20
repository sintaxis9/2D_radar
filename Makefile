CXX = g++
CXXFLAGS = -std=c++17 `pkg-config --cflags sfml-graphics` -Iinclude
LDFLAGS = `pkg-config --libs sfml-graphics`
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/Radar.o $(BUILD_DIR)/Object.o $(BUILD_DIR)/Grid.o
TARGET = radar_2d

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/Grid.o: $(SRC_DIR)/Grid.cpp $(INCLUDE_DIR)/Grid.h
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.h
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
