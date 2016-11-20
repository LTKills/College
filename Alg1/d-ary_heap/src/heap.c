/*
 * =====================================================================================
 *
 *       Filename:  heap.c
 *
 *    Description: Heap functions implementation
 *
 *        Version:  1.0
 *        Created:  11/17/16 15:42:20
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
#include <math.h>
#include <limits.h>
#include <heap.h>

#define ROOT 0
#define FIRST(pos, d) pos*d+1
#define LAST(pos, d) pos*d+d



void swap(int *vec, int a, int b) {
	int aux = vec[a];
	vec[a] = vec[b];
	vec[b] = aux;
}

/*Creates empty heap*/
struct HEAP *createHeap(void) {
	struct HEAP *heap = malloc(sizeof(struct HEAP));

	heap->vec = NULL;
	heap->n = 0;
	heap->d = 0;

	return heap;
}


void minHeapify(int *vec, int pos, int n, int d) {
	int last, first, small, i;

	small = pos;
	first = FIRST(pos, d);
	last = LAST(pos, d);

	for(i = first; i <= last && i < n; i++)
		if(vec[i] < vec[small]) small = i;

	if (small != pos) {
		swap(vec, pos, small);
		minHeapify(vec, small, n, d);
	}
}

/*Refreshes heap to accept new element*/
void buildMinHeap(int *vec, int n, int d) {
	int i;
	for(i = n/d-1; i >= 0; i--) minHeapify(vec, i, n, d);
}


/*Inserts element on heap and orders it accordingly*/
void insertHeap(struct HEAP *heap, int key, int d) {
	int i;

	heap->n++;
	heap->vec = realloc(heap->vec, sizeof(int) * heap->n);
	heap->vec[heap->n-1] = key; // Insert key at the end

	// Now rebuild heap
	buildMinHeap(heap->vec, heap->n, d);

	for(i = heap->n-1; i > 0; i--) {
		swap(heap->vec, ROOT, i);
		minHeapify(heap->vec, ROOT, i, d);
	}

}

/*Pops onde element of heap and orders*/
int removeHeap(struct HEAP *heap, int d) {
	int ans;
	if(heap->n <= 0) return INT_MIN;

	ans = heap->vec[0];

	heap->vec[0] = heap->vec[heap->n-1];
	heap->vec = realloc(heap->vec, (heap->n-1));
	heap->n--;

	// Now rebuild heap :)
	buildMinHeap(heap->vec, heap->n, d);

	return ans;
}

/*Deallocates and destroies EVERYTHING*/
void destroyHeap(struct HEAP *heap) {
	free(heap->vec);
	free(heap);
}

