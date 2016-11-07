#ifndef _STACK_H_
#define _STACK_H_

struct STACK {
	int *q;
	int total;
	int used;
};

struct STACK *createStack(int n);
void push(struct STACK *stack, int element);
int pop(struct STACK *stack);
void rmLast(struct STACK *stack);
void deleteStack(struct STACK *stack);
int emptyStack(struct STACK *stack);

#endif
