#ifndef _QUEUE_H_
#define _QUEUE_H_

struct QUEUE {
	int *q;
	int n;
};


enum {
	FALSE,
	TRUE
};


void enqueue(struct QUEUE *queue, int key);
int dequeue(struct QUEUE *queue);
void destroyQueue(struct QUEUE *queue);


#endif
