# Makefile for parser.cpp, Parser.h, tokens.cpp, Tokens.h, evaluate.cpp, Evaluate.h, Error.h, error.cpp

# Compiler
CC = g++

# Compiler flags
CFLAGS := -Wall -std=c++11

# Source files
SRC = parser.cpp tokens.cpp evaluate.cpp error.cpp main.cpp
HDR = Parser.h Tokens.h Evaluate.h Error.h

# Object files
OBJ = $(SRC:.cpp=.o)

# Executable
TARGET = calculate

# Build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile source files into object files
%.o: %.cpp $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)
