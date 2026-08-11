CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I src
SRC_DIR = src
BUILD_DIR = .
TARGET = game

SOURCES = \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/Card.cpp \
	$(SRC_DIR)/Deck.cpp \
	$(SRC_DIR)/Game.cpp \
	$(SRC_DIR)/Player.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
