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
#include <insert.h>

/*Frees the deck*/
void destroyTree(NODE *start){
	if(start == NULL) return;

	NODE *aux1 = start->left, *aux2 = start->right;


	free(start->string);
	free(start);
	destroyTree(aux1);
	destroyTree(aux2);

}


void codeGen(NODE *now, CODE **code, int nchars, int *pos, char *string){

	if(strlen(now->string) == 1){
		code[*pos]->letter = now->string[0];
		code[*pos]->string = malloc(sizeof(char)*nchars);
		strncpy(code[*pos]->string, string, nchars);
		code[*pos]->string[nchars-1] = '\0';
		(*pos)++;
		return;
	}

	/*Going left*/
	string[nchars-1] = '0';
	codeGen(now->left, code, nchars+1, pos, string);

	/*Going right*/
	string[nchars-1] = '1';
	codeGen(now->right, code, nchars+1, pos, string);

}



NODE *createNode(NODE *left, NODE *right){			//	PLEASE USE THIS SHIT ON LEAVES
	NODE *new = malloc(sizeof(NODE));

	new->next = NULL;
	new->prev = NULL;
	new->left = left;
	new->right = right;
	new->frequency = left->frequency + right->frequency;

	new->string = malloc(sizeof((strlen(left->string)+strlen(right->string))+1));

	/*Creating node string, which is the sum of strings left and right*/
	strcpy(new->string, left->string);
	strcat(new->string, right->string);

	return new;
}



/*Function for huffman compactation (.txt -> .huff)*/
void compact(char *filename){
	int i, k = 0, n = 0;
	FILE *fp;
	char *outname = calloc(strlen(filename)+2, sizeof(char));
	char *string = calloc(255, sizeof(char));
	DECK *d = createDeck();
	NODE *s0, *s1;
	CODE **codes;

	/*Taking care of initial values of DATA*/
	DATA *data = malloc(sizeof(DATA));
	data->letters = calloc(128, sizeof(int));
	data->leafes = NULL;
	data->string = NULL;
	/*=====================================*/

	fp = fopen(filename, "r");

	/*Building Letters' Vector*/
	data->string = readLine(fp);
	for(i = 0; i < strlen(data->string); i++) data->letters[(int)data->string[i]]++;
	fclose(fp);

	/*================ HUFFMAN TREE ==================*/
	// First leafes
	for(i = 0; i < 128; i++){
		if(data->letters[i] != 0){
			printf("%c\t%d\n", i, data->letters[i]);
			data->leafes = realloc(data->leafes, sizeof(NODE*)*(k+1));
			data->leafes[k] = malloc(sizeof(NODE));
			data->leafes[k]->string = malloc(sizeof(char)*2);
			data->leafes[k]->string[0] = (char) i;
			data->leafes[k]->string[1] = (char) '\0';
			data->leafes[k]->frequency = data->letters[i];
			data->leafes[k]->next = NULL;
			data->leafes[k]->prev = NULL;
			data->leafes[k]->left = NULL;
			data->leafes[k]->right = NULL;
			k++;
		}
	}

	/*Inserting leafes in order to the deck*/
	for(i = 0; i < k; i++)
		insert(d, data->leafes[i]);

	/*Creating huffman tree...*/
	while(d->size != 1){
		s0 = pop(d);
		s1 = pop(d);
		insert(d, createNode(s0, s1));
	}

	/*================================================*/


	/* GENERATING NAME.HUFF STRING*/
		for(i = 0; i < strlen(filename)-4; i++)		//	if filename is 'test.txt', outname is 'test.huff'
			outname[i] = filename[i];
		strcat(outname, ".huff");
	/* ===========================*/

	fp = fopen(outname, "w+");

	/*Generating codes*/
	codes = malloc(sizeof(CODE**)*k);
	for(i = 0; i < k; i++) codes[i] = malloc(sizeof(CODE));
	codeGen(d->start, codes, 1, &n, string);
	for(i = 0; i < k; i++) fprintf(fp, "%c - %s\n", codes[i]->letter, codes[i]->string);
	fprintf("");




	/*DEALLOCATING*/
	fclose(fp);
	destroyTree(d->start);
	free(string);
	free(codes);
	free(data->letters);
	free(data->string);
	free(data);
	free(d);
	free(outname);

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

