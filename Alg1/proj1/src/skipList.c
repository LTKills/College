#include <stdlib.h>
#include <stdio.h>
#include <list.h>


scontroler_t skipCreate(void){
	scontroler_t myControler;
	mycontroler.start = NULL;
	myControler.element = 0;
	return myControler;
}

void insertAfter(skip_t *aux, skip_t *aux){
	insert->next = aux->next;
	aux->next = insert;
	if(opt == TRUE) 

}

int againAndagain(skip_t *insert, skip_t *aux){
	int i = 0;

	/*Going down*/
	while(aux->next != NULL && strcmp(aux->next->address, insert->address) < 0) aux = aux->next;
	if(aux->down == NULL){
		insertAfter(aux, insert, FALSE);
	}
	if(aux->down != NULL) i = againAndagain(insert, aux->down);

}

void skipInsert(char *address, char *ip, scontroler_t myControler){
	skip_t *insert = malloc(sizeof(skip_t));
	skip_t *aux = myControler.start;

	/*Setting up new node*/
	insert->next = NULL;
	insert->down = NULL;
	insert->address = address;
	insert->ip = ip;
	/*Node ready*/



	/*Insert after aux*/
	insert->next = aux->next;
	insert->down = aux->down;
	aux->next = insert;

}
