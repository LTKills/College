#include <stdlib.h>
#include <stdio.h>
#include <utils.h>

// i=1
// 3 2 1
// 2 3 1
// 2 1 3
//
// i=2, (n-i) = 3-2 = 1
// 2 1 3
// 1 2 3

void bubble(int *vector, int n) {
	int i, j;
	
	for (i = 1; i < n; i++) {
		for (j = 0; j < n-i; j++) {
			if (vector[j+1] < vector[j]) {
				swap(vector, j, j+1);
			}
		}
	}
}

