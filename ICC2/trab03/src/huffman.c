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
//Coding is also art...
//				LTKills

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <file.h>
#include <insert.h>
#include <math.h>


/*Searches for the letter with the code in string*/
char fetch(CODE **codes, int ncodes, char *string){
	int i;
	for(i = 0; i < ncodes; i++)
		if(strcmp(codes[i]->string, string) == 0) return codes[i]->letter;	// return char
	return -1; // not found
}


/*Decodes binary file into new txt file*/
void decodePlz(CODE **codes, int ncodes, char *binary, FILE *fp, int bits){
	int i, j;
	char *string = NULL;
	char c;


	for(i = 0, j = 0; i < bits; i++){
		string = realloc(string, sizeof(char)*(j+2));

		if((binary[i/8] & (128 >> i%8)) != 0)	string[j] = '1';			//	DOES AN 'AND' WITH 10000000 SHIFTED >> I

		else	string[j] = '0';

		string[j+1] = '\0';
		c = fetch(codes, ncodes, string);

		j++;
		if(c != -1){						//	FOUND!
			fprintf(fp, "%c", c);
			free(string);
			string = NULL;			//	RESTARTING
			j = 0;
		}
	}
	fprintf(fp, "\n");
}


/*Frees the deck recursively*/
void destroyTree(NODE *start){
	if(start == NULL) return;

	NODE *aux1 = start->left, *aux2 = start->right;


	free(start->string);
	free(start);
	destroyTree(aux1);
	destroyTree(aux2);

}


/*Codes the binary shit*/
int writeBin(unsigned char *binary, char *code, int j){
	int i;
	for(i = 0; i < strlen(code); i++){
		if(code[i] == '1')
			binary[j/8] = binary[j/8] | (128 >> j%8);
		j++;
	}
	return j;
}

/*
 *	imagine the following binary we want to create
 *
 *
 *	10100011
 *
 *
 *	we need to shitft the number 128 (10000000) j%8 times, cuz j is the total amount of bits we have,
 *	counting past bytes (which we DO NOT want to consider)
 *
 *	if j starts at 16, we'll have:
 *
 *	j%8 == 0	j++, so we''l shift 128 (10000000) 0 times
 *	j%8 == 1	j++, so we'll shift 128 (10000000) 1 time = (01000000)
 *	j%8 == 2	j++	...
 *
 *	and so on until j == 24, then j%8 == 0 again, and we'll be on the next byte ;)
 *
 *
 * */


/*Generate the binary code for each character*/
void codeGen(NODE *now, CODE **code, int nchars, int *pos, char *string){

	if(strlen(now->string) == 1){
		code[*pos]->frequency = now->frequency;
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


/*Creates new node at the tree having left and right as sons*/
NODE *createNode(NODE *left, NODE *right){
	NODE *new = malloc(sizeof(NODE));

	new->next = NULL;
	new->prev = NULL;
	new->left = left;
	new->right = right;
	new->frequency = left->frequency + right->frequency;

	new->string = malloc(sizeof(char)*(strlen(left->string)+strlen(right->string)+1));

	/*Creating node string, which is the sum of strings left and right*/
	strcpy(new->string, left->string);
	strcat(new->string, right->string);

	return new;
}



/*Function for huffman compactation (.txt -> .huff)*/
void compact(char *filename){
	int i, k = 0, n = 0, l = 0, j = 0;
	FILE *fp;
	unsigned char *binary = NULL;
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

	/*================ HUFFMAN TREE ==================*/
	// First leafes
	for(i = 0; i < 128; i++){
		if(data->letters[i] != 0){
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


	/*Generating codes*/
	codes = malloc(sizeof(CODE*)*k);
	for(i = 0; i < k; i++) codes[i] = malloc(sizeof(CODE));
	codeGen(d->start, codes, 1, &n, string);

	/*For each letter, get it's code and print along with it*/
	for(l = 0; l < 128; l++){
		for(i = 0; i < k; i++){
			if(codes[i]->letter == l){
				fprintf(stdout, "%c - %s\n", codes[i]->letter, codes[i]->string);
				break;
			}
		}
	}
	fprintf(stdout, "-\n");



	/*Generating binary code*/
	// Allocating for binary
	for(i = 0, l = 0; i < k; i++)
		l += strlen(codes[i]->string)*codes[i]->frequency;
	l =  ceil(l/8.0);											//	in case there is no round number of bits
	binary = (unsigned char *) calloc(l+1, sizeof(unsigned char));

	// Generating binary
	for(i = 0; i < strlen(data->string); i++){	// for each character at the message
		for(n = 0; n < k; n++){					//	for each different character there is
			if(data->string[i] == codes[n]->letter){
				j = writeBin(binary, codes[n]->string, j); // j is the current number of bits
				break;
			}
		}
	}

	//Setting up last byte of binary
	binary[l] = j%8;

	for(i = 0; i < l+1; i++) printf("%d\n", binary[i]);



	/*DEALLOCATING*/
	fclose(fp);
	destroyTree(d->start);
	free(binary);
	free(string);
	for(i = 0; i < k; i++){
		free(codes[i]->string);
		free(codes[i]);
	}
	free(codes);
	free(data->leafes);
	free(data->letters);
	free(data->string);
	free(data);
	free(d);

}

/*Function for huffman decompactation (.huff -> .txt)*/
void decompact(char *filename){
	int i = 0, k = 0, bits = 0;
	FILE *fp = fopen(filename, "r");
	char c, *binary = NULL;
	CODE **codes = NULL;


	/*Getting codes along with characters*/
	c = fgetc(fp);
	while(c != '-'){
		fseek(fp, 3, SEEK_CUR);
		/*
		 *		a - 10101
		 *		^	^
		 *		r 	r => r == read
		 *
		 *		we need to jump the 3 characters between 'a' and it's code
		 *
		 * */
		codes = realloc(codes, sizeof(CODE*)*(k+1));
		codes[k] = malloc(sizeof(CODE));
		codes[k]->letter = c;	//	save de letter
		codes[k]->string = readLine(fp);	//	save the code
		k++;
		c = fgetc(fp);
	}
	fgetc(fp);		//	There is a maroterzz(marotation) \n here

	/*asd\0*/
	/*012 3*/


	//Reading binary code
	for(i = 0; !feof(fp); i++){	//	until the end of file
		c = fgetc(fp);
		if(feof(fp)) break;
		binary = realloc(binary, sizeof(char)*(i+1));
		binary[i] = c;
	}
	binary = realloc(binary, sizeof(char)*(i+1));
	binary[i] = '\0';


	bits = (strlen(binary) - 2)*8 + binary[strlen(binary)-1];		//	total number of valid bits
	decodePlz(codes, k, binary, stdout, bits);	 // decodePlz does not deal with the last 2 bytes of binary



	/*Deallocation*/
	fclose(fp);
	free(binary);
	for(i = 0; i < k; i++){
		free(codes[i]->string);
		free(codes[i]);
	}
	free(codes);

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

