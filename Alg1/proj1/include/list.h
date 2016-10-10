#ifndef _LIST_H_
#define _LIST_H_

typedef enum{
	FALSE, // 0
	TRUE // 1
} BOOL;


typedef struct list_t list_t;

struct list_t{
	list_t *next;
	char *ip;
	char *address;
};

typedef struct{
	list_t *end;
	list_t *start;
	int element;			//	number of elements
} controler_t;


controler_t createList(void);
BOOL isEmpty(controler_t myControl);
void printDatList(controler_t myControl);
void insertStart(controler_t *myControl, char *address, char *ip);
void insertEnd(controler_t *myControl, char *address, char *ip);
list_t *searchElement(controler_t myControl, char *address);
void seekAndDestroy(controler_t *myControl, char *address);
void exterminateList(controler_t *myControl);

#endif
