CC=g++
DEBUG ?=

all: main

main: hasht.o ReadWrite.o dataStructure.o request.o main.cpp 
	$(CC) $(DEBUG) -o $@ $^

ReadWrite.o: ReadWrite.cpp
	$(CC) $(DEBUG) -c $^

hasht.o: hasht.cpp
	$(CC) $(DEBUG) -c $^

request.o: request.cpp
	$(CC) $(DEBUG) -c $^

dataStructure.o: dataStructure.cpp
	$(CC) $(DEBUG) -c $^

clean:
	-rm *.o main

.PHONY: clean all
