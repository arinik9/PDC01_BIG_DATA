CC=g++
DEBUG ?=

all: main

main: hasht.o main.cpp
	$(CC) $(DEBUG) -o $@ $^

hasht.o: hasht.cpp
	$(CC) $(DEBUG) -c $^

clean:
	rm *.o main

.PHONY: clean all
