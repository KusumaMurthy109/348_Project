
# Makefile for the project

# Compiler
#CC := g++

# Compiler flags
#CFLAGS := -Wall -std=c++11

# Source files
#SRCS := evaluate.cpp main.cpp tokens.cpp

# Header files
#HEADERS := Evaluate.h Tokens.h

# Object files
#OBJS := $(SRCS:.cpp=.o)

# Executable name
#TARGET := myprogram

# Build rule for the executable
#$(TARGET): $(OBJS)
#	$(CC) $(CFLAGS) $^ -o $@

# Build rule for object files
#%.o: %.cpp $(HEADERS)
# 	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
#clean:
#	rm -f $(OBJS) $(TARGET)

# Makefile for parser.cpp and Parser.h


# MAKE FILE JUST FOR PARSER.H AND PARSER.CPP
# Compiler
#CC := g++

# Compiler flags
#CFLAGS := -Wall -std=c++11

# Source files
#SRCS := parser.cpp

# Header files
#HEADERS := Parser.h

# Object files
#OBJS := $(SRCS:.cpp=.o)

# Executable name
#TARGET := parser_program

# Build rule for the executable
#$(TARGET): $(OBJS)
#	$(CC) $(CFLAGS) $^ -o $@

# Build rule for object files
#%.o: %.cpp $(HEADERS)
#	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
#clean:
#	rm -f $(OBJS) $(TARGET)



# FOR PARSER, EVALUATE, AND TOKENS
#CC = g++
#CFLAGS = -std=c++11

# List of source files
#SRCS = main.cpp parser.cpp evaluate.cpp tokens.cpp

# List of header files
#HDRS = Tokens.h Parser.h Evaluate.h

# Object files
#OBJS = $(SRCS:.cpp=.o)

# Target executable
#TARGET = my_program

# Build rule
#$(TARGET): $(OBJS)
#	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rules for individual object files
#main.o: main.cpp $(HDRS)
#	$(CC) $(CFLAGS) -c main.cpp

#parser.o: parser.cpp Parser.h Tokens.h
#	$(CC) $(CFLAGS) -c parser.cpp

#evaluate.o: evaluate.cpp Evaluate.h Tokens.h
#	$(CC) $(CFLAGS) -c evaluate.cpp

#tokens.o: tokens.cpp Tokens.h
#	$(CC) $(CFLAGS) -c tokens.cpp

# Clean rule
#clean:
#	rm -f $(OBJS) $(TARGET)



Makefile for parser.cpp, Parser.h, tokens.cpp, Tokens.h, evaluate.cpp, Evaluate.h, Error.h, error.cpp

# Makefile

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
TARGET = myparser

# Build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile source files into object files
%.o: %.cpp $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)
