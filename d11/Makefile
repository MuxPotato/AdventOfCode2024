# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Target executable name
TARGET = executable

# Source files
SRC = src_p2.cpp

# Default rule: build the target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Rule to clean up build files
clean:
	rm -f $(TARGET)
