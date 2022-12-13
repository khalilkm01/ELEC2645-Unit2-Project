# Set compiler
CC=g++

#Compile flags (-c to output object file .o)
CFLAGS=-c -Wall

all: main.bin 

main.bin: main.o filter.o calculator.o
	$(CC) main.o filter.o calculator.o -o main.bin

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

filter.o: filter.cpp
	$(CC) $(CFLAGS) filter.cpp

calculator.o: calculator.cpp
	$(CC) $(CFLAGS) calculator.cpp

clean:
	rm *.o main.bin 