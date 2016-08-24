/*
 * =====================================================================================
 *
 *       Filename:  trab03.c
 *
 *    Description:  Trabalho 3 ICC - Professor Rodrigo Mello
 *
 *        Version:  2.3
 *        Created:  04/19/16 21:29:49
 *       Compiler:  gcc
 *
 *         Author:  Gabriel de Melo Cruz
 *   Organization:  The University of Sao Paulo
 *
 * =====================================================================================
 */



#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

unsigned int *readFile(int *size, char *name){						//Le o arquivo, modifica size e retorna o vetor de unsigned ints
	unsigned int *result;
	FILE *input;
	input = fopen(name, "r");

	fseek(input, 0, SEEK_END);
	*size = ftell(input);
	*size /= 4;

	result = malloc(sizeof(unsigned int)* *size);

	fseek(input, 0, SEEK_SET);
	fread(result, sizeof(unsigned int), *size, input);
	fclose(input);

	return result;
}


void unscramble(unsigned int *result, int size){				// Desinverte o vetor lido e armazenado em result
	unsigned int aux = 0;
	int i;

	for(i = 0; i < size/2; i++){
		aux = result[i];
		result[i] = result[size - 1 - i];
		result[size - 1 - i] = aux;
	}
}


int grabK(char name){										// Pega a primeira chave necessaria para a parte 1 do tabalho
	int k;
	k = name - 48;
	return k;
}

void grabSecret(unsigned int *result, int k, int size){		// Calcula e imprime na tela o codigo relativo à parte 1 do trabalho
	int i, j;
	for(i = 0; i < size; i++){
		for(j = 0; j < k; j++){
			result[i]/=10;
		}
		k = result[i]%10;
		printf("%d", k);
	}
	printf("\n");

}
void shiftBack(unsigned int *number){					// Shifta de volta os inteiros que contêm algum byte inválido
	*number >>= 1;
}


int checker(char coisa){																							// Checa a validade dos bytes de cada inteiro
	if(isalnum(coisa) == 0 && isblank(coisa) == 0 && coisa != ',' && coisa != ':' && coisa != '.'
	&& coisa != '(' && coisa != ')' && coisa != '!' && coisa != '?' && coisa != '\0') {
		return 0; // deu ruim -> shift
	}
	return 1; // 	wohow!
}



int occur(char *string, char *oneByte, int size){										// Verifica, para a parte 3 do trabalho, quantas vezes string aparece
	int i, k = 0, j;																	// no texto
	for(i = 0; i < 4*size; i++){
		for(j = 0; j < strlen(string) && string[j] == oneByte[i+j]; j++);
		if(j == strlen(string))
			k++;
	}
	return k;
}

int main(){
	char *name = NULL, *oneByte = NULL;
	char string[50];
	unsigned int *result = NULL;
	int size, k, op, i, j;

	name = malloc(sizeof(char)*6);
	scanf("%s", name);
	result = readFile(&size, name);
	unscramble(result, size);

	scanf("%d", &op);

	if(op == 1){											// Mapeamento de dígitos
		k = grabK(name[0]);
		grabSecret(result, k, size);
	}




	else if(op == 2){										// Descriptografia

		for(i = 0; i < size; i++){
			oneByte = (char*) &result[i];
			for(j = 0; j < 4; j++){
				if(checker(oneByte[j]) == 0){			// Caso seja inválido, shifta de volta os 4 bytes do inteiro e vai para o próximo inteiro
					shiftBack(&result[i]);
					break;
				}
			}
		}

		oneByte = (char*)result;						// Imprimindo o vetor byte a byte usando um ponteiro de chars
			printf("%s\n", oneByte);
	}




	else{										// Contagem de ocorrências

		fgetc(stdin);
		i = 0;
		do{
			string[i] = fgetc(stdin);
		}while(string[i++] != 10);
		string[i-1] = '\0';

		for(i = 0; i < size; i++){
				oneByte = (char*) &result[i];
				for(j = 0; j < 4; j++){
					if(checker(oneByte[j]) == 0){
						shiftBack(&result[i]);
						break;
					}
				}
		}
		oneByte = (char*)result;
		k = 0;
			printf("%d\n", occur(string, oneByte, size)); 					// contando ocorrências e imprimindo

	}

	free(name);
	free(result);
	return 0;
}

