CC=g++
DEBUG ?=

all: cpp

run: cpp
	python preprocessing.py ../db | ./c++/main

cpp:
	$(MAKE) -C c++

clean:
	-rm ./storage/*
	$(MAKE) -C c++ clean
	
.PHONY: clean all cpp
