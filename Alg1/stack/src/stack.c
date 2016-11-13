/*
 * =====================================================================================
 *
 *       Filename:  stack.c
 *
 *    Description:  Stack functions implememtation
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
#include <stack.h>

int isEmpty (struct STACK *stack){
	if(stack->n == 0) return TRUE;
	return FALSE;
}

void push(struct STACK *stack, int key) {
	stack->n++;
	stack->q = realloc(stack->q, sizeof(int)*stack->n);
	stack->q[stack->n-1] = key;
}

int pop(struct STACK *stack) {
	int key, i;
	if(isEmpty(stack) == TRUE) return INT_MIN;

	stack->n--;
	key = stack->q[stack->n];

	stack->q = realloc(stack->q, sizeof(int)*stack->n);

	return key;
}


void destroyStack(struct STACK *stack) {
	free(stack->q);
	free(stack);
}
