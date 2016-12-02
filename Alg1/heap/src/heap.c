/*
 * =====================================================================================
 *
 *       Filename:  heap.c
 *
 *    Description:  Binary heap functions implementation
 *
 *        Version:  1.0
 *        Created:  11/17/16 13:09:51
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

#define ROOT 0
#define LEFT(pos) (pos+1)*2-1
#define RIGHT(pos) (pos+1)*2

void swap(int *vec, int a, int b) {
	int aux = vec[a];
	vec[a] = vec[b];
	vec[b] = aux;
}

// Pops bigger elements down
void minHeapify(int *heap, int pos, int size) {
	int left = LEFT(pos), right = RIGHT(pos), tiny = pos;

	if(left < size && heap[tiny] > heap[left]) tiny = left;
	if(right < size && heap[tiny] > heap[right]) tiny = right;

	if(tiny != pos) {
		swap(heap, pos, tiny);
		minHeapify(heap, tiny, size);
	}
}

// Builds minHeap from complete random vector
void buildMinHeap(int *heap, int size) {
	int i;
	for(i = size/2-1; i >= 0; i--) minHeapify(heap, i, size);
}


// Insert element on heap and rearranges it
int *insertHeap(int *heap, int size, int key) {

	heap = realloc(heap, sizeof(int) * (size+1));
	heap[size] = key;
	buildMinHeap(heap, size+1); // reconstructs entire heap

	return heap;
}


// Pops root and returns it
int popHeap(int *heap, int size) {
	int key = heap[ROOT];
	heap[ROOT] = heap[size-1];

	minHeapify(heap, ROOT, size-1); // here the magic occurs

	heap = realloc(heap, sizeof(int) * (size-1));
	return key;
}
