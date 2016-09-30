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



/*Creates a node which points to left and right*/
void createNode(NODE *left, NODE *right){			//	DO NOT USE THIS SHIT ON LEAVES
	int i;
	NODE *new = malloc(sizeof(NODE));

	new->next = NULL;
	new->prev = NULL;
	new->left = left;
	new->right = right;
	new->frequency = -1;	// Not-leave indicator

	new->string = malloc(sizeof((strlen(left->string)+strlen(right->string))+1));

	/*Creating node string, which is the sum of strings left and right*/
	strcpy(new->string, left->string);
	strcat(new->string, right->string);
	strcat(new->string, "\0");

}



/*Insert values on the leaves by frequency and name order*/
void insertOrd(NODE *insert, NODE *start, NODE *end){
	NODE *p = start;
	char *aux;

	/*Border case START*/
	if(insert->frequency <= start->frequency){
		insert->next = start;
		insert->prev = NULL;
		start->prev = insert;
		start = insert;

		/*Ordering according to the name*/
		if(insert->frequency == start->frequency)
			while(insert->string[0] > insert->next->string[0]){
				aux = insert->string;
				insert->string = insert->next->string;
				insert->next->string = aux;
			}
		return;
	}

	/*Border case END*/
	while(insert->frequency < p->frequency){
		if(p->next == NULL && insert->frequency < p->frequency){
			insert->previous = p;
			insert->next = NULL;
			p->next = insert;
			end = insert;
			return;
		}
		p = p->next;
	}

	/*MOST CASES*/
	insert->prev = p;
	insert->next = p->next;
	p->next = insert;
	p->next->prev = insert;
	/*==========*/

	/*Ordering according to the name*/
	if(insert->frequency == insert->next->frequency)
		while(insert->string[0] > insert->next->string[0]){
			aux = insert->string;
			insert->string = insert->next->string;
			insert->next->string = aux;
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
			leaves[nleaves]->string = malloc(sizeof(char)*2);
			leaves[nleaves]->string[0] = (char) i;
			leaves[nleaves]->string[1] = '\0';
			leaves[nleaves]->frequency = freq[i];
			leaves[nleaves]->left = NULL;
			leaves[nleaves]->right = NULL;
			nleaves++;
		}
	}

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
	 *	O I J A L P		======AFTER ORDERING=====>  		L A J O P I
	 *	2 1 3 4 8 2											8 4 3 2 2 1
	 *
	 */

	/*Ordering leaves*/
	for(i = 2; i < nleaves; i++)
		insertOrd(leaves[i], start, end);

	aux = end;
	for(i = 0; aux != start;){
		if(i%2 != 0){ 				// odd
			if(aux->frequency != aux->prev->frequency){
				createNode(NULL, aux);
				i++;
			}
		}
	}

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
	int i;
	char *filename;
	filename = readLine(stdin);

	if(filename[strlen(filename)-1] == 'f')				// foo.huff <- analyze last character of line
		decompact(filename);			//	DECOMPACT
	else
		compact(filename);				// COMPACT


	free(filename);
	return 0;
}

