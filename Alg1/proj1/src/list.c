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
 *   Organization:  The University of Sao Paulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
		printf("address: %s\tip:%s\n", element->address, element->ip);
		element = element->next;
	}
	printf("\n==END PRINT==\n");
}


/*Inserts element on the beginning of the list*/
void insertStart(controler_t *myControl, char *address, char *ip){
	list_t *node = malloc(sizeof(list_t));

	node->address = address;
	node->ip = ip;
	node->next = myControl->start;

	myControl->start = node;
	myControl->element++;

}

/*Inserts element on the end of the list*/
void insertEnd(controler_t *myControl, char *address, char *ip){
	list_t *node = malloc(sizeof(list_t));

	node->address = address;
	node->ip = ip;
	node->next = NULL;

	myControl->end->next = node;
	myControl->end = node;
	myControl->element++;

}

/*Seek for an element 'look'*/
list_t *searchElement(controler_t myControl, char *address){
	list_t *littleHelper = myControl.start;

	while((littleHelper != NULL) && (strcmp(littleHelper->address, address) != 0))
		littleHelper = littleHelper->next;

	return littleHelper;
}


/*===========================DANGER ZONE=============================*/

/*Seeks for 'address' and destroys the node*/
void seekAndDestroy(controler_t *myControl, char *address){
	list_t *who = myControl->start, *target;

	if(strcmp(who->address, address) == 0){			//	solving remove start case
		myControl->start = myControl->start->next;
		free(who->address);
		free(who->ip);
		free(who);
		myControl->element--;
		return;
	}


	while((who->next != NULL) && (strcmp(who->next->address, address) != 0))
		who = who->next;

	if(who->next == NULL) return;		//	solving the not found case

	target = who->next;
	who->next = target->next;
	free(target->address);
	free(target->ip);
	free(target);
	myControl->element--;

}

/*Brutally kills a list, poor list... :'(  */
void exterminateList(controler_t *myControl){
	if(myControl->element == 0) return;

	list_t *littleHelper1 = myControl->start->next;
	list_t *littleHelper2 = littleHelper1->next;

	free(myControl->start->address);
	free(myControl->start->ip);
	free(myControl->start);

	while(littleHelper2 != NULL){
		free(littleHelper1->address);
		free(littleHelper1->ip);
		free(littleHelper1);
		littleHelper1 = littleHelper2;
		littleHelper2 = littleHelper2->next;
	}
	free(littleHelper1->address);
	free(littleHelper1->ip);
	free(littleHelper1);

	*myControl = createList();
}
