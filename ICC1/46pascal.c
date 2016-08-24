/*
 * =====================================================================================
 *
 *       Filename:  46pascal.c
 *
 *    Description:  Triangulo de Pascal
 *
 *        Version:  1.0
 *        Created:  04/29/16 23:36:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: LTKills
 *   Organization: USP
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>


void pascal(int n){
	int i, j;
	unsigned int pasc[n][n];

	for(i = 0; i < n; i++){			//	zerando os caras da matriz menos na primeira coluna
		for(j = 0; j < n; j++){
			if(j == 0) pasc[i][j] = 1;
			else pasc[i][j] = 0;
		}
	}

	for(i = 0; i < n; i++){					//	preenchendo a matriz (calculando pascal)
		for(j = 0; j <= i; j++){
			if(i != 0 && j !=0) pasc[i][j] += pasc[i-1][j] + pasc[i-1][j-1];
		}
	}


	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){ 	//	imprimindo resultados;
			if(pasc[i][j] == 0) break;
			printf("%u", pasc[i][j]);
		}
		printf("\n");
	}
}


int main(int argc, char *argv[]){
	int n;

	scanf("%d", &n);

	pascal(n);
	return 0;
}



