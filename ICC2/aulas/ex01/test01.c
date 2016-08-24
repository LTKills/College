#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include <vector.h>
#include <search.h>

void test_sequential_search() {
	int n, key;
	int *vector;
	clock_t start_time, end_time; // unsigned long
	double average_search_time;

	for (n=100; n < 10000; n+=100) {
		vector = create_sorted_vector(n);

		start_time = clock();
		for (key = 1; key <= n; key++) {
			sequential_search(vector, n, key);
		}
		end_time = clock();

		average_search_time = (end_time - start_time) / (n*1.0);
		printf("%d\t%lf\n", n, average_search_time);

		free(vector);
	}
}

void test_binary_search() {
	int n, key;
	int *vector;
	clock_t start_time, end_time; // unsigned long
	double average_search_time;

	for (n=1000; n < 100000; n+=1000) {
		vector = create_sorted_vector(n);

		start_time = clock();
		for (key = 1; key <= n; key++) {
			binary_search(vector, 0, n-1, key);
		}
		end_time = clock();

		average_search_time = (end_time - start_time) / (n*1.0);
		printf("%d\t%lf\n", n, average_search_time);

		free(vector);
	}
}

int main(int argc, char *argv[]) {

	printf("Sequential...\n");
	test_sequential_search();

	printf("Binary...\n");
	test_binary_search();

	return 0;
}






