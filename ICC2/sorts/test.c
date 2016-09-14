#include <stdlib.h>
#include <stdio.h>
#include <sorts.h>


int main(int argc, char *argv[]){
	int i, size = 8;
	int vec[8];

	vec[0] = 2;
	vec[1] = 3;
	vec[2] = 1;
	vec[3] = 0;
	vec[4] = -2;
	vec[5] = -123;
	vec[6] = 12;
	vec[7] = 1;


	for(i = 0; i < size; i++)
		printf("%d ", vec[i]);
	printf("\n");

	mergeSort(vec, 0, 7);
	for(i = 0; i < size; i++)
		printf("%d ", vec[i]);
	printf("\n");

	return 0;
}

