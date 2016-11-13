#ifndef _STACK_H_
#define _STACK_H_

struct STACK {
	int *q;
	int n;
};


enum {
	FALSE,
	TRUE
};


void push(struct STACK *stack, int key);
int pop(struct STACK *stack);
void destroyStack(struct STACK *stack);


#endif
