/*
 * =====================================================================================
 *
 *       Filename:  file.c
 *
 *    Description:  Reading, Writing and Copying File Funtions
 *
 *        Version:  1.0
 *        Created:  08/24/2016 12:55:01 PM
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
#include <math.h>
#include <file.h>

#define ENTER 10


double euclidean_distance(double *vec1, double *vec2, int len) {
	int i;
	double dist = 0;

	for(i = 0; i < len; i++)
		dist += (vec1[i]-vec2[i])*(vec1[i]-vec2[i]);

	return sqrt(dist);
}

/*Reads one line from file pointer 'file'*/
char *readLine(FILE *file){
	char *string = NULL, c;
	int size = 1;

	do{
		c = fgetc(file);
		if(c == 13) c = fgetc(file);
		string = (char *) realloc(string, sizeof(char)*size);
		string[size-1] = c;
		size++;
	}while(c != ENTER && c != EOF);
	string[size-2] = '\0';

	return string;
}



/*Reads whole content from file and stores on vec*/
void *readFile(FILE* file, TYPE opt, int *vecSize){
	void *vec = NULL;
	int type = 0;
	switch(opt){
		case CHAR:
		case UNSIGNED_CHAR:
			type = sizeof(char);
			break;
		case INT:
			type = sizeof(int);
			break;
		case DOUBLE:
			type = sizeof(double);
			break;
	}

	fseek(file, 0, SEEK_END);
	*vecSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	vec = malloc(type*(*vecSize));
	fread(vec, type, *vecSize, file);

	return vec;
}





