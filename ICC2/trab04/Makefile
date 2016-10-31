COMPILER=gcc
SRC=src/learning.c src/main.c src/file.c src/matrix.c
INCLUDE=./include
BINARY=foo
INPUTDIR=/inputs


all:
	$(COMPILER) $(SRC) -o $(BINARY) -I$(INCLUDE) -lm -g

run:
	./$(BINARY)
