CC = gcc
CFLAGS = -Wall -Wextra -I./src

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Source files
SRCS =  $(wildcard $(SRC_DIR)/*.c) \
				$(wildcard $(SRC_DIR)/commands/*.c) \
				$(wildcard $(SRC_DIR)/utils/*.c)

# Object files
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/gitkeykit

# Platform-specific settings
ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
    RM = del /Q /F
    MKDIR = mkdir
else
    RM = rm -rf
    MKDIR = mkdir -p
endif

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	$(MKDIR) $(BUILD_DIR) $(BIN_DIR) \
	$(BUILD_DIR)/$(SRC_DIR) \
	$(BUILD_DIR)/$(SRC_DIR)/commands \
	$(BUILD_DIR)/$(SRC_DIR)/utils

# Link the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile source files
$(BUILD_DIR)/%.o: %.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	$(RM) $(BUILD_DIR) $(BIN_DIR)

# Install target (Unix-like systems only)
install: all
	install -m 755 $(TARGET) /usr/local/bin/

# Phony targets
.PHONY: all clean directories install

# Dependencies
-include $(OBJS:.o=.d)