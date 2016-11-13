#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <list.h>
#include <skipList.h>
#include <string.h>


scontroler_t *skipCreate(void){
	scontroler_t *myControler = malloc(sizeof(scontroler_t));
	myControler->starts = NULL;
	myControler->levels = 0;
	return myControler;
}

void printSkipList(scontroler_t *myControler){
	skip_t *aux;
	int i;
	for(i = 0; i < myControler->levels; i++){
		aux = myControler->starts[i];
		while(aux != NULL){
			printf("%s -> m=%p d=%p) ===> ", aux->address, aux, aux->down);
			aux = aux->next;
		}
		printf("\n");
	}
}

/*Prepares a new level*/
void createNewLevel(scontroler_t *myControler){
	skip_t *big = malloc(sizeof(skip_t )), *small = malloc(sizeof(skip_t )), *aux;

	/*Setting up sentinels*/
	big->ip = NULL;
	big->next = NULL;
	big->down = NULL;
	big->address = malloc(sizeof(char)*2);
	big->address[0] = 130; // 130 cuz 126 is the biggest number on ascii
	big->address[1] = '\0';

	small->ip = NULL;
	small->next = big;		//	start -> small -> big
	small->down = NULL;
	small->address = malloc(sizeof(char)*2);
	small->address[0] = -1; // -1 cuz 0 is the smallest number on ascii
	small->address[1] = '\0';
	/*Done*/

	// Case it is not the first level
	if(myControler->levels > 0){
		small->down = myControler->starts[myControler->levels-1]; // linking first sentinels
		aux = small->down;
		while(strcmp(aux->address, big->address) != 0) aux = aux->next;
		big->down = aux; // linking last sentinels (tricky)
	}

	myControler->starts = realloc(myControler->starts, sizeof(skip_t *) * (myControler->levels+1)); // allocating one more level
	myControler->starts[myControler->levels] = small;		//	first sentinel
	myControler->levels++;
}

/*Recursive function for inserting on skiplist*/
skip_t *insertPlease(int level, skip_t *starter, skip_t *insert){
	skip_t *ohRly, *test, *start = starter;

	while(strcmp(start->next->address, insert->address) < 0) start = start->next;

	// Base case (lol that sounds funny)
	if(level == 0){
		// Preparing test
		test = malloc(sizeof(skip_t));
		test->address = malloc(sizeof(char)*(strlen(insert->address)+1));
		strcpy(test->address, insert->address);

		test->ip = malloc(sizeof(char)*(strlen(insert->ip)+1));
		strcpy(test->ip, insert->ip);
		// Done

		test->next = start->next;
		start->next = test;
		test->down = NULL;


		// Flip a coin
		if(rand()%2 == TRUE) return test;
		return NULL;
	}
	ohRly = insertPlease(level-1, start->down, insert);

	// Heads
	if(ohRly != NULL){

		// Preparing test
		test = malloc(sizeof(skip_t));
		test->address = malloc(sizeof(char)*(strlen(insert->address)+1));
		strcpy(test->address, insert->address);

		test->ip = malloc(sizeof(char)*(strlen(insert->ip)+1));
		strcpy(test->ip, insert->ip);
		// Done

		test->next = start->next;
		start->next = test;
		test->down = ohRly;

		if(rand()%2 == TRUE) return test;
	}
	// Tails
	return NULL;

}

/*Ordered insertion on skiplist*/
void insertSkip(scontroler_t *myControler, char *address, char *ip){
	int i = 0;
	// Setting up the node to be inserted (insert)
	skip_t *insert = malloc(sizeof(skip_t)), *aux, *aux2;
	insert->address = address;
	insert->ip = ip;
	insert->next = NULL;
	insert->down = NULL;
	// Done

	// Empty List case
	if(myControler->starts == NULL){
		createNewLevel(myControler);
		insert->next = myControler->starts[0]->next;
		myControler->starts[0]->next = insert;
		return;
	}

	// Recursive call
	aux2 = insertPlease((myControler->levels)-1, myControler->starts[myControler->levels-1], insert);

	// Add one more level
	if(aux2 != NULL){
		createNewLevel(myControler);
		insert->next = myControler->starts[myControler->levels-1]->next;
		myControler->starts[myControler->levels-1]->next = insert;
		insert->down = aux2;
		return;
	}
	free(insert->address);
	free(insert->ip);
	free(insert);


	return;
}



/*Fetches an specific address at the skipList*/
skip_t *skipSearch(int level, char *address, skip_t *starter){
	skip_t *start = starter;

	while(strcmp(start->next->address, address) < 0) start = start->next;

	if(strcmp(start->next->address, address) == 0) return start; // Returns the element before the one we are looking for (for rm)
	else{
		if(level == 0) return NULL; // Search hit bottom
		else return skipSearch(level-1, address, start->down);
	}
}

/*Removes an element from the skiplist*/
void skipRemove(skip_t *skiper, skip_t *aux, scontroler_t *myControler){

	// There's a bit of a trick here
	// Cuz our lists r not double-linked, we need to go through each level till the last element before the one to be removed
	while(skiper->next != aux)
	   	skiper = skiper->next;

	// And then we call the recursion
	if(aux->down != NULL)
		skipRemove(skiper->down, aux->down, myControler);

	// And we free
	skiper->next = aux->next;
	free(aux->ip);
	free(aux->address);
	free(aux);
	return;
}

/*Deallocates all the skiplist*/
void exterminateSkipList(scontroler_t *myControler){
	skip_t *aux, *aux2;
	int i;

	// For each level
	for(i = 0; i < myControler->levels; i++){
		aux = myControler->starts[i]; // Beginning of the level
		aux2 = aux->next;
		while(aux2 != NULL){ // Start freeing
			aux2 = aux->next;
			free(aux->ip);
			free(aux->address);
			free(aux);
			aux = aux2;
		}
	}

	free(myControler->starts); // Free the vector with all the first nodes
}














