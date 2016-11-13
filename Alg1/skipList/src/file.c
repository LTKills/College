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
#include <file.h>



/*Reads one line from file pointer 'file'*/
char *readLine(FILE *file, char delim){
	char *string = NULL, c;
	int size = 1;

	do{
		c = fgetc(file);
		string = (char *) realloc(string, sizeof(char)*size);
		string[size-1] = c;
		size++;
	}while(c != delim && c != EOF);
	string[size-2] = '\0';

	return string;
}



/*Reads whole content from file and stores on vec*/
void *readFile(FILE* file, TYPE opt, int *vecSize){
	void *vec = NULL;
	int type;
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





