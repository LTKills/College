#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


void merge(int *vector, int start, int middle, int end){
	int *vec1, *vec2, i, j, k;

	vec1 = malloc(sizeof(int)*(middle-start+1));
	vec2 = malloc(sizeof(int)*(end-middle+1));

	/*COPYING VECTOR*/
	for(i = start; i < middle; i++) vec1[i-start] = vector[i];
	vec1[i-start] = INT_MAX; // PUT SENTINEL
	for(i = middle; i <= end; i++) vec2[i-middle] = vector[i];
	vec2[i-middle] = INT_MAX;

	i = 0;
	j = 0;

	/*REARRANGING ORIGINAL VECTOR*/
	for(k = 0; k <= end-start; k++){
		if(vec1[j] == vec2[i] == INT_MAX) break;

		if(vec2[i] > vec1[j])
			vector[k] = vec1[j++];
		else vector[k] = vec2[i++];
	}

	free(vec1);
	free(vec2);

}

/*Recursion call*/
void mergeSort(int *vector, int start, int end){
	int middle = (end+start)/2;

	if(start >= end) return;

	mergeSort(vector, start, middle);
	mergeSort(vector, middle+1, end);

	merge(vector, start, middle, end);

}
