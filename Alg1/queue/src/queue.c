/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  Queue functions implememtation
 *
 *        Version:  1.0
 *        Created:  11/13/16 18:07:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTkills
 *   Organization:  The University of Sao Paulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <queue.h>

int isEmpty (struct QUEUE *queue){
	if(queue->n == 0) return TRUE;
	return FALSE;
}

void enqueue(struct QUEUE *queue, int key) {
	queue->n++;
	queue->q = realloc(queue->q, sizeof(int)*queue->n);
	queue->q[queue->n-1] = key;
}

int dequeue(struct QUEUE *queue) {
	int key, i;
	if(isEmpty(queue) == TRUE) return INT_MIN;

	key = queue->q[0];
	for(i = 1; i < queue->n; i++) queue->q[i-1] = queue->q[i];

	queue->n--;
	queue->q = realloc(queue->q, sizeof(int)*queue->n);

	return key;
}


void destroyQueue(struct QUEUE *queue) {
	free(queue->q);
	free(queue);
}
