/*
 * =====================================================================================
 *
 *       Filename:  sudoku.c
 *
 *    Description:  Sudoku
 *
 *        Version:  1.0
 *        Created:  05/05/16 15:14:41
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

#define row 16
#define col 16
#define ENTER 10

char **matrixAlloc(int rows, int cols){
	char **mr;
	int i;
	mr = (char **) malloc(sizeof(char*)*rows);
	for(i = 0; i < rows; i++){
		mr[i] = (char*) malloc(sizeof(char)*cols);
	}
	return mr;
}

char **matrixFileRead(char **mr, int rows, int cols){
	int i, j;
	FILE *fp;
	char name[10];

	scanf("%s", name);
	fp = fopen(name, "r");

	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
			fscanf(fp, "%c ", &mr[i][j]);

	fclose(fp);
	return mr;
}

void matrixPrint(char **mr, int rows, int cols){
	int i, j;
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			printf("%c", mr[i][j]);
		}
		printf("\n");
	}
}

void matrixFree(char **mr, int rows){
	int i, j;
	for(i = 0; i < rows; i++)
		free(mr[i]);
	free(mr);
}

char hex(int k){
	if(k >= 10)
		return k + 55;
	else
		return k + 48;
}

char *takeOut(char *vec, char exterminate){
	int i, j;

	for(i = 0; i < 16; i++)
		if(vec[i] == exterminate) vec[i] = 'z';

	return vec;
}

char check(char **mr, int i, int j){
	int k, l;
	char great;
	char *vec;

	vec = (char*) malloc(sizeof(char) * 16);

	for(k = 0; k < 16; k++)	vec[k] = hex(k);			//	Iniciando o vetor de possibilidades

	for(k = 0; k < row; k++)					//	Checando coluna, variando linhas
		vec = takeOut(vec, mr[k][j]);

	for(k = 0; k < col; k++)					//	Checando linha, variando colunas
		vec = takeOut(vec, mr[i][k]);

	// Percorrendo o quadrado atual (shit has gonna serious)


	for(k = (i/4)*4; k < ((i/4)*4)+4; k++)
		for(l = (j/4)*4; l < ((j/4)*4)+4; l++)
			vec = takeOut(vec, mr[k][l]);

	//	Checando unicidade dos elementos validos
	l = 0;
	for(k = 0; k < 16; k++)
		if(vec[k] != 'z'){
			great = vec[k];
			l++;
		}
	free(vec);

	if(l == 1) return great;

	return '.';			// retorna um valor invalido '.'

}


int main(int argc, char *argv[]){
	int i, j, k, dots = 0;
	char **mr;
	char **mc;

	mr = matrixAlloc(row,  col);
	mr = matrixFileRead(mr, row, col);

	for(i = 0; i < row; i++)			//	conta o numero de espaços livres
		for(j = 0; j < col; j++)
			if(mr[i][j] == '.')	dots++;


	while(dots > 0){						//	Enquanto houver pontos
		//	Percorrendo a matriz
		for(i = 0; i < row; i++){
			for(j = 0; j < col; j++){
				if(mr[i][j] == '.'){
					mr[i][j] = check(mr, i, j);
					if(mr[i][j] != '.'){
						dots--;
					}
				}
			}
		}
	}

	matrixPrint(mr, row, col);
	matrixFree(mr, row);
	return 0;
}

