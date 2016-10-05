#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <file.h>
#include <insert.h>


void printDeck(DECK *d){
	int i;
	NODE *aux = d->start;
	for(i = 0; i < d->size; i++){
		printf("string = %s\tfrequency = %d\n", aux->string, aux->frequency);
		aux = aux->next;
	}
}



/*Create empty deck*/
DECK *createDeck(void){
	DECK *p = malloc(sizeof(DECK));
	p->start = NULL;
	p->size = 0;
	return p;
}


/*Pop first element of the deck*/
NODE *pop(DECK *d){
	NODE *aux = d->start;

	d->start = d->start->next;
	d->size--;

	return aux;
}

/*Insert element into deck in appropriate order*/
void insert(DECK *d, NODE *n){
	int i;
	NODE *aux = d->start;

	/*FOR THE FIRST TIME*/
	if(d->start == NULL){
		d->start = n;
		d->size++;
		return;
	}

	for(i = 1; i <= d->size; i++){
		if(n->frequency > aux->frequency){
			if(i == d->size){					//	INSERT AFTER END
				n->prev = aux;
				n->next = NULL;
				aux->next = n;
				break;
			}
			else aux = aux->next;
		}
		else if(n->frequency < aux->frequency){
			if(i == 1){							//	INSERT BEFORE START
				n->prev = NULL;
				n->next = aux;
				aux->prev = n;
				d->start = n;
				break;
			}
			else{
				n->prev = aux->prev;			//	INSERT MIDDLE -> BEFORE AUX
				n->next = aux;
				aux->prev->next = n;
				aux->prev = n;
				break;
			}
		}
		else if(n->frequency == aux->frequency){			//	N == AUX
			if(strcmp(n->string, aux->string) < 0){
				if(i == 1){						// INSERT BEFORE START
					n->prev = NULL;
					n->next = aux;
					aux->prev = n;
					d->start = n;
					break;
				}
				else{						//	INSERT MIDDLE -> BEFORE AUX
					n->prev = aux->prev;
					n->next = aux;
					aux->prev->next = n;
					aux->prev = n;
					break;
				}
			}
			else{
				if(i == d->size){				//	INSERT AFTER END
					n->prev = aux;
					n->next = NULL;
					aux->next = n;
					break;
				}
				else aux = aux->next;			// MOVE
			}
		}
	}
	d->size++;
}



