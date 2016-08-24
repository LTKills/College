#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int *create_random_vector(int n, int bound) {
	int i;
	int *vector = (int *) malloc(n * sizeof(int));

	srand(time(NULL));
	for (i = 0; i < n; i++) {
		vector[i] = rand() % bound;
	}
	return vector;
}

int *create_asc_sorted_vector(int n) {
	int i;
	int *vector = (int *) malloc(n * sizeof(int));

	for (i = 0; i < n; i++) {
		vector[i] = i+1;
	}
	return vector;
}

int *create_desc_sorted_vector(int n) {
	int i;
	int *vector = (int *) malloc(n * sizeof(int));

	for (i = 0; i < n; i++) {
		vector[i] = n-i;
	}
	return vector;
}

void print_vector(int *vector, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d\n", vector[i]);
	}
}


