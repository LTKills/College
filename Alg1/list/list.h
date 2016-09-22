#ifndef _LIST_H_
#define _LIST_H_

typedef enum{
	FALSE, // 0
	TRUE // 1
} BOOL;


typedef struct list_t list_t;

struct list_t{
	list_t *next;
	int value;
};

typedef struct{
	list_t *end;
	list_t *start;
	int element;
} controler_t;


controler_t createList(void);
BOOL isEmpty(controler_t myControl);
void insertStart(controler_t *myControl, int val);
void insertEnd(controler_t *myControl, int val);
list_t *searchElement(controler_t myControl, int look);
void seekAndDestroy(controler_t *myControl, int look);
void printDatList(controler_t myControl);
controler_t exterminateList(controler_t myControl);

#endif
