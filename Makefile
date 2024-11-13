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

# Add this near the top, after the variables but before the platform-specific settings
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
