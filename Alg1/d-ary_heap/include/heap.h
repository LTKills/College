#ifndef _HEAP_H_
#define _HEAP_H_


struct HEAP {
	int *vec;
	int n;
	int d;
};


struct HEAP *createHeap(void);
void insertHeap(struct HEAP *heap, int key, int d);
int removeHeap(struct HEAP *heap, int d);
void destroyHeap(struct HEAP *heap);


#endif
