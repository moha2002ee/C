# Compiler and linker settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = 

# Project files
TARGET = Test1
SRC = Test1.cpp Event.cpp
OBJ = $(SRC:.cpp=.o)

# Build the main executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile .cpp files into .o files
%.o: %.cpp Event.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean generated files
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: clean
