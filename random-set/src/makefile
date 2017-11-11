#!/usr/bin/make
## makefile
## Mac Radigan

.PHONY: clean clobber build run

.DEFAULT_GOAL := default

CC = g++

target = random-set

date = $(shell date +%F)

results         = ../results

default: build

build:
	$(CC) -std=c++1z -o $(target) $(target).cc

run:
	./$(target) |tee $(results)/$(target).out

clobber: clean
	-rm -f ./$(target)

clean:
	-rm -f ./*.o

## *EOF*
