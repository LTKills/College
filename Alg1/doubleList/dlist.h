#ifndef _DLIST_H_
#define _DLIST_H_

typedef enum{
	FALSE, // 0
	TRUE // 1
} BOOL;


typedef struct dlist_t dlist_t;

struct dlist_t{
	dlist_t *next;
	dlist_t *previous;
	int value;
};

typedef struct{
	dlist_t *end;
	dlist_t *start;
	int element;
} dcontroler_t;


dcontroler_t createList(void);
BOOL isEmpty(dcontroler_t myControl);
void insertStart(dcontroler_t *myControl, int val);
void insertEnd(dcontroler_t *myControl, int val);
dlist_t *searchElement(dcontroler_t myControl, int look);
void seekAndDestroy(dcontroler_t *myControl, int look);
void printDatList(dcontroler_t myControl);
dcontroler_t exterminateList(dcontroler_t myControl);

#endif
