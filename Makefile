# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

# Source file
SRC = temp.c

# Executable name
EXEC = temp_converter

# Default target
all: $(EXEC)

# Build rule
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

# Clean rule
clean:
	rm -f $(EXEC)

.PHONY: all clean
