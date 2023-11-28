# Compiler and flags
CC = gcc

CFLAGS=-Wall `sdl2-config --cflags --libs` -lm -lSDL2_image -lSDL2_ttf
# Directories
SRC_DIR = .
OBJ_DIR = ../obj
BIN_DIR = ../bin

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Executable name
# TARGET = $(BIN_DIR)/test

# Default target
all: $(BIN_DIR) $(OBJS)

# Build executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) test.c -o $@

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# PHONY targets
.PHONY: all clean
