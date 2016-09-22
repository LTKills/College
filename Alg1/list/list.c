/*
 * =====================================================================================
 *
 *       Filename:  list.c
 *
 *    Description:  Simply-linked list implementation
 *
 *        Version:  1.0
 *        Created:  09/21/2016 09:47:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  Yo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <list.h>

/*Creates empty list*/
controler_t createList(void){
	controler_t control;

	control.end = NULL;
	control.start = NULL;
	control.element = 0;

	return control;
}

/*Verifies if the list is or not empty*/
BOOL isEmpty(controler_t myControl){
	if(myControl.element == 0) return TRUE;
	return FALSE;
}

/*Prints full list*/
void printDatList(controler_t myControl){
	list_t *element = myControl.start;
	int i;

	if(isEmpty(myControl) == TRUE){
		printf("Empty list\n");
		return;
	}

	printf("\n==START PRINT==\n");
	for(i = 0; i < myControl.element; i++){
		printf("%d ", element->value);
		element = element->next;
	}
	printf("\n==END PRINT==\n");
}


/*Inserts element on the beginning of the list*/
void insertStart(controler_t *myControl, int val){
	list_t *node = malloc(sizeof(list_t));

	node->value = val;
	node->next = myControl->start;

	myControl->start = node;
	myControl->element++;

}

/*Inserts element on the end of the list*/
void insertEnd(controler_t *myControl, int val){
	list_t *node = malloc(sizeof(list_t));

	node->value = val;
	node->next = NULL;

	myControl->end->next = node;
	myControl->end = node;
	myControl->element++;

}

/*Seek for an element 'look'*/
list_t *searchElement(controler_t myControl, int look){
	list_t *littleHelper = myControl.start;

	while(littleHelper->value != look){
		littleHelper = littleHelper->next;
	}

	return littleHelper;
}


//===========================DANGER ZONE=============================

/*Seeks for 'look' and destroys the node*/
void seekAndDestroy(controler_t *myControl, int look){
	list_t *who = myControl->start, *target;

	while(who->next->value != look){			//	doesn't solve the border cases
		who = who->next;
	}

	target = who->next;
	who->next = target->next;
	free(target);

}

/*Brutally kills a list, poor list...*/
controler_t exterminateList(controler_t myControl){
	list_t *littleHelper1 = myControl.start->next;
	list_t *littleHelper2 = littleHelper1->next;

	free(myControl.start);

	while(littleHelper2 != NULL){
		free(littleHelper1);
		littleHelper1 = littleHelper2;
		littleHelper2 = littleHelper2->next;
	}
	free(littleHelper1);

	return createList();
}
