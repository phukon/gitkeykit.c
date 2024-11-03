CC = gcc
CFLAGS = -Wall -Wextra -I./src
SRCS = src/main.c src/gpg_handler.c src/git_config.c src/logger.c
OBJS = $(SRCS:.c=.o)
TARGET = gitkeykit

ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)