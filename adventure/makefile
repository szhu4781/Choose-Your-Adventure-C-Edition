# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Target executable name
TARGET = adventure.exe

# Source files
SOURCES = adv.cpp player.cpp event.cpp elite.cpp boss.cpp loot.cpp prog.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# To create object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	del /f /q $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: clean
