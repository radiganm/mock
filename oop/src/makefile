#!/usr/bin/make
## makefile
## Mac Radigan

.PHONY: clean clobber build run test

.DEFAULT_GOAL := default

CC = gcc

target  = oop
suffx   = ansi_c
results = $(target)__$(suffx)

date = $(shell date +%F)

SRC =       \
  common.c  \
  stack.c   \
  map.c

results         = ../../results

default: build

build:
	#$(CC) -g -ansi -std=c99 -o $(target)  -I../include $(SRC) $(target).c
	$(CC) -g -ansi -std=c99 -o test_stack -I../include $(SRC) test_stack.c
	$(CC) -g -ansi -std=c99 -o test_map   -I../include $(SRC) test_map.c

run:
	#./$(target) |tee $(results)/$(results).out

test:
	#./$(target)
	./test_stack
	./test_map

clobber: clean
	#-rm -f ./$(target)
	-rm -f ./test_stack
	-rm -f ./test_map

clean:
	-rm -f ./*.o

## *EOF*
