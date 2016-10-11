#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

typedef struct skip_t skip_t;

struct skip_t{
	skip_t *next, *down;
	char *address;
	char *ip;
	int isEnd;
};

typedef struct{
	skip_t *start;
	int element;
} scontroler_t;



#endif
