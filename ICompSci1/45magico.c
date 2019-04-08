/*
 * =====================================================================================
 *
 *       Filename:  45magico.c
 *
 *    Description:  Quadrado magico
 *
 *        Version:  1.0
 *        Created:  04/28/16 19:59:45
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


int main(int argc, char *argv[]){
	int i, j, n;
	int **cube = NULL;
	int sum = 0, now = 0;

	scanf("%d", &n);

	cube = (int**) malloc(sizeof(int*) * n);		//	alocando para a matriz cube
	for(i = 0; i < n; i++){
		cube[i] = (int*) malloc(sizeof(int) * n);
	}

	//	lendo os caracteres da matriz
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			scanf("%d", &cube[i][j]);
		}
	}
	//	colocando a primeira soma em sum
	for(j = 0; j < n; j++){
			sum += cube[0][j];
	}


	//	conferindo linhas
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
				now += cube[i][j];
		}
		if(now != sum){
			printf("NAO\n");
			return 0;
		}
		now = 0;
	}

	//	conferindo colunas
	for(j = 0; j < n; j++){
		for(i = 0; i < n; i++){
			now += cube[i][j];
		}
		if(now != sum){
			printf("NAO\n");
			return 0;
		}
		now = 0;
	}


	now = 0;
	//	conferindo diagonal principal
	for(i = 0; i < n; i++){
		now += cube[i][i];
	}


	if(now != sum){
		printf("NAO\n");
		return 0;
	}

	//	conferindo diagonal secundaria
	for(i = n-1; i >= 0; i--){
		now = 0;
		for(j = 0; j < n; j++){
			now += cube[i][j];
		}
	}
	if(now != sum){
		printf("NAO\n");
		return 0;
	}

	printf("SIM\n");


	for(i = 0; i < n; i++){
		free(cube[i]);
	}

	free(cube);
	return 0;
}




