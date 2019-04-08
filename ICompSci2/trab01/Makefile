all:
	gcc -o shell ./src/shell.c ./src/myregex.c -I./include -O3
run:
	./shell
bug:
	valgrind --leak-check=full ./shell
rm:
	rm *idx *tmp *dat
