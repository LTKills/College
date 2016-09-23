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


dcontroler_t create_dList(void);
BOOL is_dEmpty(dcontroler_t myControl);
void insert_dStart(dcontroler_t *myControl, int val);
void insert_dEnd(dcontroler_t *myControl, int val);
dlist_t *search_dElement(dcontroler_t myControl, int look);
void seekAnd_dDestroy(dcontroler_t *myControl, int look);
void printDat_dList(dcontroler_t myControl);
dcontroler_t exterminate_dList(dcontroler_t myControl);

#endif
