all:
	gcc src/fourier.c src/file.c -o t -I./include -lm -g
run:
	./t < Case_01.in > out
rm:
	rm out my-beautiful-new-audio.raw
bug:
	valgrind ./t < Case_01.in > out


