#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <stack.h>

struct STACK *createStack(int n) {
	struct STACK *stack = malloc(sizeof(struct STACK));

	stack->q = calloc(n, sizeof(int));
	stack->total = n;
	stack->used = 0;

	return stack;
}

void push(struct STACK *stack, int element) {
	if(stack->used == stack->total) return;
	stack->q[stack->used] = element;
	stack->used++;
}

int pop(struct STACK *stack) {
	return stack->q[stack->used-1];
}

void rmLast(struct STACK *stack) {
	stack->used--;
}

void deleteStack(struct STACK *stack) {
	free(stack->q);
	free(stack);
}

int emptyStack(struct STACK *stack) {
	if(stack->used == 0) return TRUE; // is empty
	return FALSE;
}

