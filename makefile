# Set compiler
CC=g++

#Compile flags (-c to output object file .o)
CFLAGS=-c -Wall

all: main.bin 

main.bin: main.o circle.o
	$(CC) main.o circle.o -o main.bin

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

circle.o: circle.cpp
	$(CC) $(CFLAGS) circle.cpp

clean:
	rm *.o main.bin 