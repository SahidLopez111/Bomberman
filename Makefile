# Makefile for Bomberman Game
# Compiler and flags
CXX = g++

# Detect macOS and set SFML paths
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    # macOS with Homebrew
    SFML_PREFIX := $(shell brew --prefix sfml 2>/dev/null || echo /opt/homebrew/opt/sfml)
    SFML_INCLUDE := $(SFML_PREFIX)/include
    SFML_LIB := $(SFML_PREFIX)/lib
    CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I$(SFML_INCLUDE)
    LDFLAGS = -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
else
    # Linux (default)
    CXXFLAGS = -std=c++17 -Wall -Wextra -O2
    LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
ASSETS_DIR = assets
VID_DIR = vid

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Target executable
TARGET = bomberman

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete! Run ./$(TARGET) to play"

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Clean complete"

# Rebuild everything
rebuild: clean all

# Install dependencies (macOS)
install-deps-mac:
	brew install sfml

# Install dependencies (Ubuntu/Debian)
install-deps-ubuntu:
	sudo apt-get update
	sudo apt-get install libsfml-dev

# Run the game
run: $(TARGET)
	./$(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all          - Build the game (default)"
	@echo "  clean        - Remove build files"
	@echo "  rebuild      - Clean and rebuild"
	@echo "  run          - Build and run the game"
	@echo "  install-deps-mac    - Install SFML on macOS (requires Homebrew)"
	@echo "  install-deps-ubuntu - Install SFML on Ubuntu/Debian"
	@echo "  help         - Show this help message"

.PHONY: all clean rebuild run install-deps-mac install-deps-ubuntu help

