COMPILER=gcc
INCLUDE=./include
SRC=src/main.c src/file.c src/hash.c
OUTPUT=t


all:
	$(COMPILER) -o $(OUTPUT) $(SRC) -I$(INCLUDE) -g -lm
run:
	./$(OUTPUT)
