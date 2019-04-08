#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


char *readLine(void){			// funcao que le o nome do maluco
	int i = 0;
	char c;
	char *string = NULL;
	
	do{
		c = fgetc(stdin);
		string = realloc(string, sizeof(char)*(i+1));
		string[i++] = c;
	}while(c != 10);
	string[i-1] = '\0';
	
	return string;
}


int main(int argc, char *argv[]){
	char *string;
	int i, k = 0, j = 0;
	string = readLine();		//	lendo o nome do maluco
	
	for(i = 0; i < strlen(string); i++){	//	vendo a quantidade de espaços
		if(isspace(string[i]) != 0)
			k++;
	}
	
	for(i = 0; i < strlen(string) && j != k; i++)	//	indo até o último nome
		if(isspace(string[i]) != 0)
			j++;
	
	
	while(string[i] != '\0'){			//	imprimindo o ultimo nome
		if(string[i] == '\0')
			printf("Eu sou bobo\n");			// teste loko!
		printf("%c", toupper(string[i++]));
	}
	printf(", ");
		
	j = 0; i = 0;
	while(j != k){
		if(isspace(string[i]) != 0)		//	imprimindo os demais nomes
			j++;
		if(j != k)
			printf("%c", string[i++]);
		if(string[i] == '\0')
			printf("Eu sou bobo\n");
	}
	printf("\n");
	
	
	free(string);
	return 0;
}

