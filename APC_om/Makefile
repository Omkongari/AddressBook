CC = gcc
CFLAGS = -Wall -g
OBJ = addition.o multiplication.o division.o subtraction.o other.o validate.o main.o
DEPS = apc.h
TARGET = apc_calc

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
