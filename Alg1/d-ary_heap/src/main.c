/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Main function for heap implementation
 *
 *        Version:  1.0
 *        Created:  11/17/16 15:04:35
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
#include <heap.h>

enum {
	PROGNAME,
	FILENAME,
	NARGS
};

int main(int argc, char *argv[]) {
	int i, n, d, *elements;
	FILE *fp;
	struct HEAP *heap = createHeap();

	if(argc != NARGS) {
		printf("usage: %s filename\n", argv[PROGNAME]);
		return -1;
	}

	fp = fopen(argv[FILENAME], "r");

	// Reading inputs
	fscanf(fp, "%d", &n);

	elements = malloc(sizeof(int) * n);
	for(i = 0; i < n; i++)	fscanf(fp, "%d", &elements[i]);

	printf("Present us with a D your royal highness: ");
	scanf("%d", &d);
	// Inputs read

	for(i = 0; i < n; i++)	insertHeap(heap, elements[i], d); // Inserting on heap

	// Removing and printing
	printf("\n==========YAY! REMOVING==========\n");
	for(i = 0; i < n; i++) printf("%d\n", removeHeap(heap, d));


	// Freeing
	fclose(fp);
	destroyHeap(heap);
	free(elements);
	return 0;
}


