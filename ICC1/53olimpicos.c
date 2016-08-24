/*
 * =====================================================================================
 *
 *       Filename:  53olimpicos.c
 *
 *    Description:  Jogos Olimpicos
 *
 *        Version:  1.0
 *        Created:  05/21/2016 07:56:48 PM
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


void swap(double *a, double *b){
	double aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

int **swapRowsInt(int **medals, int a, int b){
	int i;
	int aux[500];
	for(i = 0; i < 3; i++)
		aux[i] = medals[a][i];
	for(i = 0; i < 3; i++)
		medals[a][i] = medals[b][i];
	for(i = 0; i < 3; i++)
		medals[b][i] = aux[i];

	return medals;
}

char **swapRowsChar(char **names, int a, int b){
	int i;
	char aux[500];
	for(i = 0; i < 3; i++)
		aux[i] = names[a][i];
	for(i = 0; i < 3; i++)
		names[a][i] = names[b][i];
	for(i = 0; i < 3; i++)
		names[b][i] = aux[i];

	return names;
}

int main(void){
	int i, j, k;
	int **medals;
	char **names;
	double vec[500];
	scanf("%d", &k);

	medals = (int**) malloc(sizeof(int*)*k);
	names = (char**) malloc(sizeof(char*)*k);
	for(i = 0; i < k; i++){
		names[i] = malloc(sizeof(char)*4);
		medals[i] = malloc(sizeof(char)*3);
	}



	for(i = 0; i < k; i++){
		scanf("%s", names[i]);
		for(j = 0; j < 3; j++)		//	recebendo nome
			scanf("%d", &medals[i][j]); // recebendo medalhas
	}

	for(i = 0; i < k; i++)						//	transforma a quantidade de medalhas em valor
		for(j = 0; j < 3; j++)
			vec[i] += (double) medals[i][j] * 1/pow(1000, j);


	for(i = 0; i < k; i++)				//	ordena os valores tranformados
		for(j = 1; j < k; j++){
			if(vec[j] > vec[j-1]){
				swap(&vec[j], &vec[j-1]);
				swapRowsInt(medals, j, j-1);		//	ordena tambem as matrizes medals e names
				swapRowsChar(names, j, j-1);
			}
		}

	for(i = 0; i < k; i++){						//	imprime
		printf("%s ", names[i]);
		for(j = 0; j < 3; j++)
			printf("%d ", medals[i][j]);
		printf("\n");
	}

	for(i = 0; i < k; i++) free(medals[i]);
	free(medals);

	for(i = 0; i < k; i++) free(names[i]);
	free(names);

	return 0;
}

