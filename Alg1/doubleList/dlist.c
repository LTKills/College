/*
 * =====================================================================================
 *
 *       Filename:  dlist.c
 *
 *    Description:  Double Linked List Implementation
 *
 *        Version:  1.0
 *        Created:  09/22/2016 07:19:02 PM
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
#include <dlist.h>

/*Creates empty list*/
dcontroler_t create_dList(void){
	dcontroler_t myControl;

	myControl.end = NULL;
	myControl.start = NULL;
	myControl.element = 0;

	return myControl;
}

/*Checks if a list is or not empty*/
BOOL is_dEmpty(dcontroler_t myControl){
	if (myControl.element == 0) return TRUE;
	else return FALSE;
}

/*Insert element at the begining of the list*/
void insert_dStart(dcontroler_t *myControl, int val){
	dlist_t *new = malloc(sizeof(dlist_t));

	new->next = myControl->start;
	new->previous = NULL;
	new->value = val;

	if(myControl->element != 0)
		myControl->start->previous = new;

	myControl->start = new;

	if(myControl->element == 0) myControl->end = new;

	myControl->element++;
}

/*Insert element at the end of the list*/
void insert_dEnd(dcontroler_t *myControl, int val){
	dlist_t *new = malloc(sizeof(dlist_t));

	new->previous = myControl->end;
	new->next = NULL;
	new->value = val;

	if(myControl->element != 0)
		myControl->end->next = new;

	myControl->end = new;

	if(myControl->element == 0) myControl->start = new;

	myControl->element++;
}

/*Searches for the node which contains the element 'look'*/
dlist_t *search_dElement(dcontroler_t myControl, int look){
	int i;
	dlist_t *now = myControl.start;

	for(i = 0; i < myControl.element; i++){
		if(now->value == look) return now;
		now = now->next;
	}
	return NULL;			//	Returns NULL if it does not find
}

/*Prints the full list*/
void printDat_dList(dcontroler_t myControl){
	dlist_t *element = myControl.start;
	int i;

	if(is_dEmpty(myControl) == TRUE){
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

//=========================DANGER ZONE==============================

/*Searches and exterminates the node which contains the element 'look'*/
void seekAnd_dDestroy(dcontroler_t *myControl, int look){
	dlist_t *who = myControl->start, *target;

	while(who->next->value != look){			//	doesn't solve the border cases
		who = who->next;
	}

	target = who->next;
	who->next = target->next;
	target->next->previous = who;
	free(target);							//	Die motherfucker dieee!

}


/*Completely destoys a*/
dcontroler_t exterminate_dList(dcontroler_t myControl){
	dlist_t *littleHelper1 = myControl.start->next;
	dlist_t *littleHelper2 = littleHelper1->next;

	free(myControl.start);

	while(littleHelper2 != NULL){
		free(littleHelper1);
		littleHelper1 = littleHelper2;
		littleHelper2 = littleHelper2->next;
	}
	free(littleHelper1);

	return create_dList();

}
