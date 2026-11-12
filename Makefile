# Implementation choice (IMPL) lives in config.mk
include config.mk

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Source files
SRCS = main.c team.c teamlist_$(IMPL).c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = team_ep

# Phony targets
.PHONY: all compile run clean

# Default target
all: compile run

# Compile target
compile: $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f *.o $(TARGET)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files
$(TARGET): $(OBJS) config.mk
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)