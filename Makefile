# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Target executable
TARGET = game

# Source file
SRCS = game2.1.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the game
run: all
	./$(TARGET)
