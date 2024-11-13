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

# variables for architecture and OS detection
ifeq ($(OS),Windows_NT)
    DETECTED_OS := windows
    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        DETECTED_ARCH := x86_64
    else ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        DETECTED_ARCH := x86
    else
        DETECTED_ARCH := $(PROCESSOR_ARCHITECTURE)
    endif
else
    DETECTED_OS := $(shell uname -s | tr '[:upper:]' '[:lower:]')
    DETECTED_ARCH := $(shell uname -m)
    # Normalize architecture names
    ifeq ($(DETECTED_ARCH),x86_64)
        DETECTED_ARCH := amd64
    endif
    ifeq ($(DETECTED_ARCH),aarch64)
        DETECTED_ARCH := arm64
    endif
endif

# Modify the target executable name to include OS and architecture
TARGET = $(BIN_DIR)/gitkeykit-$(DETECTED_OS)-$(DETECTED_ARCH)

# Platform-specific settings
ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
    RM = cmd /C rmdir /S /Q
    MKDIR = cmd /C mkdir
    # Define Windows-specific directory creation
directories:
	@if not exist "$(BUILD_DIR)" $(MKDIR) "$(BUILD_DIR)"
	@if not exist "$(BIN_DIR)" $(MKDIR) "$(BIN_DIR)"
	@if not exist "$(BUILD_DIR)\$(SRC_DIR)" $(MKDIR) "$(BUILD_DIR)\$(SRC_DIR)"
	@if not exist "$(BUILD_DIR)\$(SRC_DIR)\commands" $(MKDIR) "$(BUILD_DIR)\$(SRC_DIR)\commands"
	@if not exist "$(BUILD_DIR)\$(SRC_DIR)\utils" $(MKDIR) "$(BUILD_DIR)\$(SRC_DIR)\utils"
else
    RM = rm -rf
    MKDIR = mkdir -p
    # Define Unix directory creation
directories:
	$(MKDIR) $(BUILD_DIR)
	$(MKDIR) $(BIN_DIR)
	$(MKDIR) $(BUILD_DIR)/$(SRC_DIR)
	$(MKDIR) $(BUILD_DIR)/$(SRC_DIR)/commands
	$(MKDIR) $(BUILD_DIR)/$(SRC_DIR)/utils
endif

all: directories $(TARGET)

# Link the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile source files
$(BUILD_DIR)/%.o: %.c
ifeq ($(OS),Windows_NT)
	@if not exist "$(dir $@)" $(MKDIR) "$(subst /,\,$(dir $@))"
else
	$(MKDIR) $(dir $@)
endif
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	$(RM) $(BUILD_DIR)
	$(RM) $(BIN_DIR)

# Install target (Unix-like systems only)
install: all
	install -m 755 $(TARGET) /usr/local/bin/

# Phony targets
.PHONY: all clean directories install

# Dependencies
-include $(OBJS:.o=.d)
