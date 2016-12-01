/*
 * =====================================================================================
 *
 *       Filename:  counting.c
 *
 *    Description:  Counting sort implemetation
 *
 *        Version:  1.0
 *        Created:  11/30/16 22:43:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  The University of Sao Paulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>


int *countingSort(int *vec, int size) {
	int max = INT_MIN, min = INT_MAX, i;
	int *aux, *ans;

	// find max value
	for(i = 0; i < size; i++){
		if(max < vec[i]) max = vec[i];
		if(min > vec[i]) min = vec[i];
	}

	aux = calloc(max-min+1, sizeof(int));

	// creating frequency vector
	for(i = 0; i < size; i++) aux[vec[i]-min]++;

	// creating acumulated frequency vector
	for(i = 1; i < max-min+1; i++) aux[i] += aux[i-1];

	// giving answers
	ans = malloc(size, sizeof(int));

	for(i = size-1; i >= 0; i--) {
		aux[vec[i]-min]--;
		ans[aux[vec[i]-min]] = vec[i];
	}

	free(aux);
	free(vec);
	return ans;
}
