#include <stdlib.h>
#include <stdio.h>
#include <sorts.h>


int main(int argc, char *argv[]){
	int i, size = 5;
	int vec[5];

	vec[0] = 2;
	vec[1] = 3;
	vec[2] = 1;
	vec[3] = -1;
	vec[4] = 4;

	insertionSort(vec, size);
	for(i = 0; i < size; i++)
		printf("%d ", vec[i]);
	printf("\n");

	return 0;
}

