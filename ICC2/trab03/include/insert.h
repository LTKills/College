#ifndef _INSERT_H_
#define _INSERT_H_

typedef struct NODE NODE;

typedef struct{
	char *string;
	char letter;
} CODE;

typedef struct{
	char *string;
	int *letters;
	NODE **leafes;
} DATA;

typedef struct{
	NODE *start;
	int size;
} DECK;

struct NODE{
	NODE *left, *right, *next, *prev;
	char *string;
	int frequency;
};

void printDeck(DECK *d);
void insert(DECK *d, NODE *n);
DECK *createDeck(void);
NODE *pop(DECK *d);

#endif
