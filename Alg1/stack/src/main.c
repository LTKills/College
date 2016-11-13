/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Main function for binary tree testing
 *
 *        Version:  1.0
 *        Created:  11/11/16 17:32:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  The University of Sao Pulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <stack.h>

enum {
	PROGNAME,
	ELEMENTS,
	OPERATIONS,
	NARGS
};

int main(int argc, char *argv[]) {
	int i, j, key, op;
	struct STACK *stack = calloc(1, sizeof(struct STACK));


	if(argc != NARGS) {
		printf("usage: %s elements operations\n", argv[PROGNAME]);
		return -1;
	}

	for(i = 0; i < atoi(argv[ELEMENTS]); i++) {
		scanf("%d", &key);
		push(stack, key);
	}

	for(i = 0; i < atoi(argv[OPERATIONS]); i++) {
		printf("1.Push\t2.Pop\t3.Print\n");
		scanf("%d", &op);

		switch(op) {
			case 1:
				printf("Key: ");
				scanf("%d", &key);
				printf("\n");
				push(stack, key);
				break;

			case 2:
				printf("%d\n", pop(stack));
				break;

			case 3:
				for(j = 0; j < stack->n; j++) printf("%d ", stack->q[j]);
				printf("\n");
				break;

		}
	}

	destroyStack(stack);
	return 0;
}


