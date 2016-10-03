/*
 * =====================================================================================
 *
 *       Filename:  huffman.c
 *
 *    Description:  Huffman coding for text compactation
 *
 *        Version:  1.0
 *        Created:  09/10/16 16:24:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  USP
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <file.h>

int lol = 0;
typedef struct NODE NODE;

typedef struct{
	char symbol;
	char *bits;
} RELATE;


struct NODE{
	NODE *left, *right, *next, *prev;
	char *string;
	int frequency;
};

void inOrder(NODE* node){
	//printf("INORDER\n");
	if (node){
		inOrder(node->left);
		printf("%d - %s\n", node->frequency, node->string);
		inOrder(node->right);
	}
}

/*Creates a node which points to left and right*/
NODE *createNode(NODE *left, NODE *right){			//	DO NOT USE THIS SHIT ON LEAVES
	printf("CREATE NODE%d\n", lol);
	lol++;
	NODE *new = malloc(sizeof(NODE));

	new->next = NULL;
	new->prev = NULL;
	new->left = left;
	new->right = right;
	new->frequency = left->frequency+right->frequency;

	new->string = malloc(sizeof((strlen(left->string)+strlen(right->string))+1));

	/*Creating node string, which is the sum of strings left and right*/
	strcpy(new->string, left->string);
	strcat(new->string, right->string);

	printf("Returning => %p\t%s\t%d\n", new, new->string, new->frequency);
	return new;
}

/*Inserting related with start*/
void insertStart(NODE *insert, NODE **start){
	if(insert->frequency > (*start)->frequency){				//	insert BEFORE start
		insert->prev = NULL;
		insert->next = *start;
		(*start)->prev = insert;
		*start = insert;
	}else{
		if(strcmp(insert->string, (*start)->string) > 0){		// insert BEFORE start
			insert->prev = NULL;
			insert->next = *start;
			(*start)->prev = insert;
			*start = insert;
		}else{													// insert AFTER start
			insert->prev = *start;
			insert->next = (*start)->next;
			(*start)->next = insert;
			(*start)->next->prev = insert;
		}
	}
}

/*Inserting related with end*/
void insertEnd(NODE *insert, NODE **end){
	if(insert->frequency > (*end)->frequency){				//	insert BEFORE end
		printf("Insert before1 end\n");
		printf("Insert is %s\n", insert->string);
		insert->next = *end;
		insert->prev = (*end)->prev;
		(*end)->prev->next = insert;
		(*end)->prev = insert;
	}else if(insert->frequency < (*end)->frequency){		//	insert AFTER end
		printf("Insert after end\n");
		insert->prev = *end;
		insert->next = (*end)->next;
		if((*end)->next != NULL){
			(*end)->next->prev = insert;
		}
		(*end)->next = insert;
	}else{
		if(strcmp(insert->string, (*end)->string) > 0){		// insert BEFORE end
			printf("Insert before2 end\n");
			printf("Insert is %s\n", insert->string);
			printf("end-%p\tend->next=%p\tend->prev=%p\tinsert=%p\tinsert->prev=%p\tinsert->next=%p\n", *end, (*end)->next, (*end)->prev, insert, insert->prev, insert->next);
			insert->next = *end;
			insert->prev = (*end)->prev;
			(*end)->prev->next = insert;
			(*end)->prev = insert;
			printf("end-%p\tend->next=%p\tend->prev=%p\tinsert=%p\tinsert->prev=%p\tinsert->next=%p\n", *end, (*end)->next, (*end)->prev, insert, insert->prev, insert->next);
		}else{													// insert AFTER end
			printf("Insert after end\n");
			insert->prev = *end;
			insert->next = (*end)->next;
			if((*end)->next != NULL){
				(*end)->next->prev = insert;
			}
			(*end)->next = insert;
		}
	}
}

void insertOrd(NODE *insert, NODE **start, NODE **end){
	NODE *p = *start;
	char *aux;
	printf("insertOrd\n");

	/*Border case START*/
	if(p->frequency <= insert->frequency){
		printf("insertStart\n");
		insertStart(insert, start);						//			I wanna insert BEFORE or AFTER start
		return;
	}

	while(insert->frequency < p->frequency && p != *end){
		p = p->next; 													// p is always AFTER insert
	}

	/*Border case END*/
	if(p == *end){
		printf("insertEnd\n");
		insertEnd(insert, end);							//	I want to insert BEFORE or AFTER end
		return;
	}


	/*MOST CASES*/
	insert->next = p;
	insert->prev = p->prev;
	insert->prev->next = insert;
	p->prev = insert;
	/*==========*/

	/*Ordering according to the name*/
	if(insert->frequency == insert->next->frequency){
		//printf("entrei name2\n");
		while(strcmp(insert->string, insert->next->string) < 0 && insert->frequency == insert->next->frequency){
			aux = insert->string;
			insert->string = insert->next->string;
			insert->next->string = aux;
			insert = insert->next;
		}
	}
}

/*Function for huffman compactation (.txt -> .huff)*/
void compact(char *filename){
	int i, nleaves = 0;
	int *freq = calloc(128, sizeof(int));
	char *string = NULL;
	FILE *fp = NULL;
	NODE **leaves = NULL, *start, *end, *aux;

	fp = fopen(filename, "r");
	string = readLine(fp);

	for(i = 0; i < strlen(string); i++) freq[(int) string[i]]++; // counting frequencies

	// creating leaves
	for(i = 0; i < 128; i++){
		if(freq[i] != 0){
			leaves = realloc(leaves, sizeof(NODE*)*(nleaves+1));
			leaves[nleaves] = malloc(sizeof(NODE));
			leaves[nleaves]->string = malloc(sizeof(char)*2);
			leaves[nleaves]->string[0] = (char) i;
			leaves[nleaves]->string[1] = '\0';
			leaves[nleaves]->frequency = freq[i];
			leaves[nleaves]->left = NULL;
			leaves[nleaves]->right = NULL;
			nleaves++;
		}
	}

	printf("Leaves created...\n");
	/*Setting manually all this starting shit*/
	if(leaves[0]->frequency > leaves[1]->frequency){ // Frequency has priority
		start = leaves[0];
		end = leaves[1];
		leaves[0]->next = leaves[1];
		leaves[1]->prev = leaves[0];
		leaves[0]->prev = NULL;
		leaves[1]->next = NULL;
	}else if(leaves[0]->frequency < leaves[1]->frequency){ // Most frequent first
		start = leaves[1];
		end = leaves[0];
		leaves[1]->next = leaves[0];
		leaves[0]->prev = leaves[1];
		leaves[1]->prev = NULL;
		leaves[0]->next = NULL;
	}else if(leaves[0]->frequency == leaves[1]->frequency && leaves[0]->string[0] <= leaves[1]->string[0]){ // If frequency is a tie, order by alphabetically
		start = leaves[0];
		end = leaves[1];
		leaves[0]->next = leaves[1];
		leaves[1]->prev = leaves[0];
		leaves[0]->prev = NULL;
		leaves[1]->next = NULL;
	}else{							//	A comes b4 B
		start = leaves[1];
		end = leaves[0];
		leaves[1]->next = leaves[0];
		leaves[0]->prev = leaves[1];
		leaves[1]->prev = NULL;
		leaves[0]->next = NULL;
	}
	/*==============UGLY===============*/


	/*
	 *															  TIE
	 *															   ^
	 *															  ---
	 *	O I J A L P		======AFTER ORDERING=====>  		L A J P O I
	 *	2 1 3 4 8 2											8 4 3 2 2 1
	 *
	 */

	printf("Ordering now...\n");
	/*Ordering leaves*/
	//printf("start=%p\tend=%p\n", start, end);
	//printf("start->prev=%p\tstart->next=%p\tend->prev=%p\tend->next=%p\n", start->prev, start->next, end->prev, end->next);
	for(i = 2; i < nleaves; i++){
		insertOrd(leaves[i], &start, &end);
	//	printf("start=%p\tend=%p\n", start, end);
	//	printf("start->prev=%p\tstart->next=%p\tend->prev=%p\tend->next=%p\n", start->prev, start->next, end->prev, end->next);
	}



	printf("All leaves insered\n");

	while(start != end){
		aux = start;
		printf("========================================================================================================\n");
		while(aux != NULL){
			printf("\n\n\nFreq=%d\tstring=%s\tme=%p\tnext=%p\tprev=%p\n", aux->frequency, aux->string, aux, aux->next, aux->prev);
			aux = aux->next;
		}

		//printf("END == %p\n", end);
		aux = createNode(end, end->prev);
		printf("Aux is %p\n", aux);
		insertOrd(aux, &start , &end);
		end = end->prev->prev;
	}
	printf("Am I here?\n");

	end = createNode(start, start->next);
	start = end;
	inOrder(start);


	//Deallocation
	free(leaves);
	free(freq);
	free(string);
	fclose(fp);
}

/*Function for huffman decompactation (.huff -> .txt)*/
void decompact(char *filename){
}


int main(int argc, char *argv[]){
	char *filename;
	filename = readLine(stdin);

	if(filename[strlen(filename)-1] == 'f')		// foo.huff <- analyze last character of line
		decompact(filename);			//	DECOMPACT
	else
		compact(filename);				// COMPACT


	free(filename);
	return 0;
}

