#include <stdlib.h>
#include <stdio.h>
#include <vector.h>
#include <bubble.h>

enum {
	PROGNAME,
	N,
	NARGS
};

int main(int argc, char *argv[]) {
	int n;
	int *vector;

	if (argc != NARGS) {
		printf("usage: %s n\n", argv[PROGNAME]);
		return -1;
	}

	n = atoi(argv[N]);
	vector = create_random_vector(n, 5*n);

	printf("Before...\n");
	print_vector(vector, n);

	bubble(vector, n);

	printf("After...\n");
	print_vector(vector, n);

	free(vector);

	return 0;
}








