#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

typedef struct skip_t skip_t;

struct skip_t{
	skip_t *next, *down;
	char *address;
	char *ip;
};

typedef struct{
	skip_t **starts;
	int levels;
} scontroler_t;


void printSkipList(scontroler_t *myControler);
scontroler_t *skipCreate(void);
void insertSkip(scontroler_t *myControler, char *address, char *ip);
skip_t *skipSearch(int level, char *address, skip_t *start);
void skipRemove(skip_t *skiper);

#endif
