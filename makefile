.PHONY: all clean
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Executable name
TARGET = mypreprocessor

# Source files
SRC = main.c preprocessor.c comment_removal.c file_inclusion.c macro_handler.c

# Build executable
all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Remove generated files
clean:
	rm -f $(TARGET) *.o *.i
