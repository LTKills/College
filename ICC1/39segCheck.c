/*
 * =====================================================================================
 *
 *       Filename:  39segCheck.c
 *
 *    Description:  Verificação de segmentos
 *
 *        Version:  1.0
 *        Created:  04/23/16 23:08:10
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
	char c, *string = NULL;
	int i = 0;
	do{
		c = fgetc(stdin);
		string = (char*)realloc(string, sizeof(char)*(i+1));
		*(string+i) = c;
		i++;
	}while(c != 10);
	*(string+i-1) = '\0';

	return string;
}


int main(int argc, char *argv[]){
	char *c = NULL, *string = NULL, letter;
	int i, j, k = 0;

	string = readLine();
	c = readLine();

	if(strcmp(string, c) == 0){
		printf("%s %s %s\n", c, string, "SIM");
		return 0;

	}else if(strlen(string) > strlen(c)){
		for(i = 0; i < strlen(string); i++){
			for(j = i; j-i < strlen(c); j++){
				if(c[j-i] == string[j])
					k++;
			}
			if(k == strlen(c)){
				printf("%s %s %s\n", c, string, "SIM");
				return 0;
			}
			k = 0;
		}
		printf("%s %s %s\n", c, string, "NAO");
		return 0;

	}else if(strlen(c) > strlen(string)){
		for(i = 0; i < strlen(c); i++){
			for(j = i; j-i < strlen(string); j++){
				if(string[j-i] == c[j])
					k++;
			}
				if(k == strlen(string)){
					printf("%s %s %s\n", string, c, "SIM");
					return 0;
				}
				k = 0;
		}
		printf("%s %s %s\n", string, c, "NAO");
		return 0;
	}else{
		for(i = 0; i < strlen(string); i++){
			if(*(string+i) > *(c+i)){
				printf("%s %s %s\n", c, string, "NAO");
				return 0;
			}
			if(*(string + i) < *(c + i)){
				printf("%s %s %s\n", string, c, "NAO");
				return 0;
			}
		}
	}
}





