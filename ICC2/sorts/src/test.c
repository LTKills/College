#include <stdlib.h>
#include <stdio.h>
#include <sorts.h>
#include <vector.h>

#define SIZE 1000000
#define BOUND 10000000

int main(int argc, char *argv[]){
	int i, size;
	int *vec;

	printf("BEFORE\n");
	vec = randVec(BOUND, SIZE);
	//printVec(vec, SIZE);

	printf("\n\nAFTER\n");
	mergeSort(vec, 0, SIZE-1);
	//printVec(vec, SIZE);


	free(vec);
	return 0;
}

