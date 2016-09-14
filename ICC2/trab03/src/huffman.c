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

#define COMMAND 0
#define FILENAME 1
#define TOKNUM 2

compact(char &filename){

}

decompact(char &filename){

}

int main(int argc, char *argv[]){
	int i;
	char *line, *tok, **tokens = NULL;
	line = readLine(stdin);

	tokens = (char**) malloc(sizeof(char*)*TOKNUM);

	tokens[FILENAME] = NULL;

	//Tokens[0] -> command
	//Tokens[1] -> file name

	/*PARSING INPUT STRING INTO COMMAND AND FILENAME*/
	tok = strtok(line, " ");
	tokens[COMMAND] = malloc(sizeof(char)*(strlen(tok)+1));
	strcpy(tokens[COMMAND], tok);


	tok = strtok(NULL, " ");

	for(i = 0; tok[i] != '.'; i++) {
		tokens[FILENAME] = realloc(tokens[FILENAME], sizeof(char)*(i+1));
		tokens[FILENAME][i] = tok[i]; // removing extension from FILENAME
	}

	tokens[FILENAME] = realloc(tokens[FILENAME], sizeof(char)*(i+1));
	tokens[FILENAME][i] = '\0'; // removing extension from FILENAME
	/*==============================================*/
	free(line);


	if(strcmp(tokens[COMMAND], "descompactar") == 0){				//	DECOMPACT
		decompact(tokens[FILENAME]);
	}
	else if(strcmp(tokens[COMMAND], "compactar") == 0){			// 	COMPACT
		compact(tokens[FILENAME]);
	}


	for(i = 0; i < 2; i++) free(tokens[i]);
	free(tokens);
	return 0;
}

