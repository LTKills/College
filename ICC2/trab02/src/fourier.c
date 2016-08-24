/*
 * =====================================================================================
 *
 *       Filename:  fourier.c
 *
 *    Description:  Fourier Transform for Noise Removing on Audio Files
 *
 *        Version:  1.0
 *        Created:  08/24/2016 12:52:42 PM
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
#include <file.h>


#define SIZE UNSIGNED_CHAR

int *inductGen(int c, unsigned char *raw, int size){

}

int *magsDecrease(int *induct, int size){

}


int main(int argc, char *argv[]){
	char *file;
	unsigned char *raw;
	int c, size, i, *induct, *mags;
	FILE *fp;

	file = readLine(stdin);
	fp = fopen(file, "rb");
	free(file);
	scanf("%d", &c);

	raw = (unsigned char*)readFile(fp, SIZE, &size);

	induct = inductGen(c, raw, size);
	mags = magsDecrease(induct, size);

	// Test
	for(i = 0; i < size; i++)
		printf("%c", vec[i]);
	printf("\n");


	free(vec);
	fclose(fp);
	return 0;
}

