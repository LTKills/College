/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Main for heap implementation
 *
 *        Version:  1.0
 *        Created:  11/17/16 13:07:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  The Universty of Sao Paulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <heap.h>

enum {
	PROGNAME,
	SIZE,
	NARGS
};

int main(int argc, char *argv[]) {
	int i, key;
	int *heap = NULL;

	if(argc != NARGS) {
		printf("usage: %s size\n", argv[PROGNAME]);
		return -1;
	}

	// Inserting elements
	for(i = 0; i < atoi(argv[SIZE]); i++) {
		scanf("%d", &key);
		heap = insertHeap(heap, i, key);
	}


	// Printing heap
	printf("NO POP\n");
	for(i = 0; i < atoi(argv[SIZE]); i++) printf("%d ", heap[i]);
	printf("\n");

	// Printing heap (with pop)
	printf("WITH POP\n");
	for(i = atoi(argv[SIZE]); i > 0; i--) {
		key = popHeap(heap, i);
		printf("%d ", key);
	}
	printf("\n");

	return 0;
}

