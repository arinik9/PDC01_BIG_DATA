CC=g++
DEBUG ?=
DB ?=../db

all: cpp

run: cpp
	python preprocessing.py $(DB) | ./c++/main

cpp:
	$(MAKE) -C c++
	mkdir -p storage

clean:
	-rm ./storage/*
	$(MAKE) -C c++ clean
	
.PHONY: clean all cpp
