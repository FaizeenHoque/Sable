CC = gcc
CFLAGS = -Wall -Wextra -g

SRC_DIR = src
BUILD_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
TARGET = $(BUILD_DIR)/sable

# Default target
all: $(BUILD_DIR) $(TARGET)

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link all object files
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES)

# Compile each .c into its corresponding .o inside build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/sable.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Optional: run directly
run: all
	./$(TARGET)
