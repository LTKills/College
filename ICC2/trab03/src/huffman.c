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
	NODE *left, *right;
	char *string;
	int size, myValue; // myValue is used here to indecate wether the node's value is 0 or 1
};


/*Function for huffman compactation (.txt -> .huff)*/
void compact(char *filename){
	printf("Compact\n");
}

/*Function for huffman decompactation (.huff -> .txt)*/
void decompact(char *filename){
	int i, n, lim, *data;
	FILE *huff;
	RELATE *table = NULL;



	huff = fopen(filename, "r");

	for(i = 0; fgetc(huff) != '-'; i++){ 		// Reading symbols' table
		table[i] = realloc(table, sizeof(RELATE)*(i+1));
		fscanf(huff, "%c - ", &table[i].symbol);
		table[i]->bits = readLine(huff);
	}


	for(i = 0; !feof(huff); i++){					// Reading compacted text
		data = realloc(data, sizeof(int)*(i+1));
		data[i] = (int) fgetc(huff);
	}

	n = i;
	lim = (int) data[n];
	for(i = 0; i < n-1; i++){
		// DUNNO WHAT TO DO HERE :'(
	}


	//  SOME CRAZY BIG SHIT FUCK HAPPENING HERE, TOTALLY LOST :(((


	fclose(huff);
}


int main(int argc, char *argv[]){
	int i;
	char *filename;
	filename = readLine(stdin);

	if(filename[strlen(filename)-1] == 'f')				//	DECOMPACT
		decompact(filename);			// foo.huff <- analyze last character of line
	else
		compact(filename);				// COMPACT


	free(filename);
	return 0;
}

