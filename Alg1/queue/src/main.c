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
#include <queue.h>

enum {
	PROGNAME,
	ELEMENTS,
	OPERATIONS,
	NARGS
};

int main(int argc, char *argv[]) {
	int i, j, key, op;
	struct QUEUE *queue = calloc(1, sizeof(struct QUEUE));


	if(argc != NARGS) {
		printf("usage: %s elements operations\n", argv[PROGNAME]);
		return -1;
	}

	for(i = 0; i < atoi(argv[ELEMENTS]); i++) {
		scanf("%d", &key);
		enqueue(queue, key);
	}

	for(i = 0; i < atoi(argv[OPERATIONS]); i++) {
		printf("1.Enqueue\t2.Dequeue\t3.Print\n");
		scanf("%d", &op);

		switch(op) {
			case 1:
				printf("Key: ");
				scanf("%d", &key);
				printf("\n");
				enqueue(queue, key);
				break;

			case 2:
				printf("%d\n", dequeue(queue));
				break;

			case 3:
				for(j = 0; j < queue->n; j++) printf("%d ", queue->q[j]);
				printf("\n");
				break;

		}
	}

	destroyQueue(queue);
	return 0;
}


