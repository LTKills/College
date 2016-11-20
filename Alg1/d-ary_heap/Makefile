COMPILER=gcc
SRC=src/main.c src/heap.c
INCLUDE=./include
BINARY=t
INPUT=elements.dat


all:
	$(COMPILER) -o $(BINARY) $(SRC) -I$(INCLUDE) -g -lm

run:
	./randGen.sh > $(INPUT)
	./$(BINARY) $(INPUT)
