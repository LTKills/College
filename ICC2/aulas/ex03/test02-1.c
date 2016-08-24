#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector.h>
#include <insertion.h>

int main(int argc, char *argv[]) {
	int n;
	int *vector;
	clock_t start_time, end_time;

	printf("Best case...\n");

	for (n = 100000; n < (int) pow(2, 21); n += 10000) {
		vector = create_asc_sorted_vector(n);

		start_time = clock();
		insertion(vector, n);
		end_time = clock();
		printf("%d\t%lf\n", n, 
				(end_time - start_time) / (CLOCKS_PER_SEC * 1.0));

		free(vector);
	}

	printf("Worst case...\n");

	for (n = 1000; n < (int) pow(2, 15); n += 1000) {
		vector = create_desc_sorted_vector(n);

		start_time = clock();
		insertion(vector, n);
		end_time = clock();
		printf("%d\t%lf\n", n, 
				(end_time - start_time) / (CLOCKS_PER_SEC * 1.0));

		free(vector);
	}

	return 0;
}








