/*
 * =====================================================================================
 *
 *       Filename:  35stringChar.c
 *
 *    Description:  Procura ocorrências de um caracter em uma string
 *
 *        Version:  1.0
 *        Created:  04/23/16 19:44:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  The University of Sao Paulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *readLine(void){
	int i = 0;
	char c;
	char *string = NULL;

	do{
		c = fgetc(stdin);
		string = (char*) realloc(string, sizeof(char)*(i+1));
		string[i++] = c;
	}while(c != 10);
		string = (char*) realloc(string, sizeof(char)*(i+1));
		string[i] = '\0';
		return string;
}


int contChar(char *string, char c){
	int i, k = 0;

	for(i = 0; i < strlen(string); i++){
		if(string[i] == c){
			k++;
		}
	}

	return k;
}

int main(int argc, char *argv[]){
	char *string = NULL;
	char c;
	int i, k;

	string = readLine();
	scanf("%c", &c);

	printf("%d\n", contChar(string, c));

	free(string);
	return 0;
}







