/*
 * =====================================================================================
 *
 *       Filename:  47matrixMult.c
 *
 *    Description:  Multiplicacao de matrizes
 *
 *        Version:  1.0
 *        Created:  04/30/16 00:09:27
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

void matrixMult(int **m1, int **m2, int row1, int col1, int row2, int col2){
	int i, j, k = 0;
	int mr[row1][col2];

	for(i = 0; i < col1; i++){			//	zerando elementos da matriz resposta
		for(j = 0; j < row2; j++){
			mr[i][j] = 0;
		}
	}



	for(i = 0; i < row1; i++){			//	fixando linhas de m1
		for(j = 0; j < row2; j++){		//	fixando colunas de m2
			for(k = 0; k < row2; k++){		//	percorrendo linhas de m1 e colunas de m2
			mr[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}


	for(i = 0; i < row1; i++){					//	imprimindo matriz resposta
		for(j = 0; j < col2; j++){
			printf("%d ", mr[i][j]);
		}
		printf("\n");
	}
}

int **matrixRead(int row, int col){
	int i, j;
	int **matrix = NULL;

	matrix = (int**) malloc(sizeof(int*) * row);			// alocando para a matriz a ser lida
	for(i = 0; i < row; i++){
		matrix[i] = (int*) malloc(sizeof(int) * col);
	}

	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){					//	lendo a matriz
			scanf("%d", &matrix[i][j]);
		}
	}
	return matrix;
}

int main(int argc, char *argv[]){
	int row1, row2, col1, col2, i;
	int **m1 = NULL, **m2 = NULL;

	scanf("%d %d", &row1, &col1);			//	lendo matriz 1
	m1 = matrixRead(row1, col1);

	scanf("%d %d", &row2, &col2);			//	lendo matriz 2
	m2 = matrixRead(row2, col2);


	matrixMult(m1, m2, row1, col1, row2, col2);


	for(i = 0; i < row1; i++){			//	desalocando matrizes
		free(m1[i]);
	}

	for(i = 0; i < row2; i++){
		free(m2[i]);
	}
	free(m1);
	free(m2);
	return 0;
}



