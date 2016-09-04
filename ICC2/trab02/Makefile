all:
	gcc src/fourier.c src/file.c -o t -I./include -lm -Wall -g
run:
	./t
bug:
	gcc src/fourier-test.c src/file-test.c -o t -I./include -lm -Wall -g
	./t < Case_01.in
