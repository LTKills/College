/*
 * =====================================================================================
 *
 *       Filename:  heap.c
 *
 *    Description:  Heapsort implementation with maxheap
 *
 *        Version:  1.0
 *        Created:  11/30/16 16:01:28
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
#include <utils.h>

#define LEFT(pos) (pos+1)*2-1
#define RIGHT(pos) (pos+1)*2

void maxHeapify(int *vec, int pos, int size) {
	int left = LEFT(pos), right = RIGHT(pos), large = pos;

	if(left < size && vec[left] > vec[large]) large = left;
	if(right < size && vec[right] > vec[large]) large = right;

	if(large != pos) {
		swap(vec, large, pos);
		maxHeapify(vec, large, size);
	}
}

void buildMaxHeap(int *vec, int size) {
	int i;
	for(i = size/2-1; i >= 0; i--) {
		maxHeapify(vec, i, size);
	}
}

void heapSort(int *vec, int size) {
	int  i;
	buildMaxHeap(vec, size);

	for(i = size-1; i >= 0; i--) {
		swap(vec, i, 0);
		maxHeapify(vec, 0, i);
	}
}

