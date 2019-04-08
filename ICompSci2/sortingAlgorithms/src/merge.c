#include <stdlib.h>
#include <stdio.h>

/*Merges two subvectors orderly*/
void merge(int *vec, int start, int mid, int end) {
	int i = start, j = mid+1, k;
	int *aux;

	aux = malloc(sizeof(int) * (end-start+1));

	for(k = start; k <= end; k++) aux[k-start] = vec[k]; // copying to auxiliary array

	for(k = start; k <= end; k++) {
		if(i > mid) { 	// Transpassed left vector
			vec[k] = aux[j-start];
			j++;
		} else if(j > end) {	// Transpassed right vector
			vec[k] = aux[i-start];
			i++;
		} else if(aux[j-start] > aux[i-start]) { // Get from left
			vec[k] = aux[i-start];
			i++;
		} else { // Get from right
			vec[k] = aux[j-start];
			j++;
		}
	}

	free(aux);
}

/*Calling function merge recursively*/
void mergeSort(int *vec, int start, int end) {
	int mid = (start + end)/2;
	if(start == end) return;

	mergeSort(vec, start, mid);
	mergeSort(vec, mid+1, end);

	merge(vec, start, mid, end);
}
