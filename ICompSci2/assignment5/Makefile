COMPILER=gcc
INCLUDE=./include
SRC=src/main.c src/graph.c src/stack.c
OUTPUT=t


all:
	$(COMPILER) -o $(OUTPUT) $(SRC) -I$(INCLUDE) -g -lm
run:
	./$(OUTPUT)
