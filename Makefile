CC = gcc
CFLAGS = -Wall -Wextra
SRCS = src/main.c src/system_check.c src/key_management.c src/git_config.c
OBJS = $(SRCS:.c=.o)
TARGET = gitkeykit

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)