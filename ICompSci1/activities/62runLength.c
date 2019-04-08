/*
 * =====================================================================================
 *
 *       Filename:  61runLenght.c
 *
 *    Description:  Run Length
 *
 *        Version:  1.0
 *        Created:  06/12/16 10:45:56
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
#include <string.h>

int **matrixCreate(int row, int col){
	int i;
	int **mat;

	mat = (int**) calloc(row, sizeof(int*));
	for(i = 0; i < row; i++)
		mat[i] = (int*) calloc(col, sizeof(int));

	return mat;
}

void matrixRead(int **mat, int row, int col, FILE *fp){
	int i, j;
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			fscanf(fp, "%d", &mat[i][j]);
		}
	}
}

int main(int argc, char *argv[]){
	int i, j, k = 1, row, col, max;
	int **mat;
	char name[20], check[10];
	FILE *fp;

	scanf("%s", name);
	fp = fopen(name, "r");
	fscanf(fp, "%s", check);
	fscanf(fp, "%d %d", &col, &row);
	fscanf(fp, "%d", &max);
	printf("P8\n%d %d\n%d\n", col, row, max);

	mat = matrixCreate(row, col+1);
	matrixRead(mat, row, col, fp);
	fclose(fp);

	for(i = 0; i < row; i++)
		mat[i][col] = -1;


	//==========	Compact here  ===================
	for(i = 0; i < row; i++){
		for(j = 1; j <= col; j++){
			if(mat[i][j] == mat[i][j-1]) k++;
			if(mat[i][j] != mat[i][j-1]){
				if(k > 3)
					printf("@ %d %d ", mat[i][j-1], k);
				else if(k == 3) printf("%d %d %d ", mat[i][j-3], mat[i][j-2], mat[i][j-1]);
				else if(k == 2) printf("%d %d ", mat[i][j-2], mat[i][j-1]);
				else if(k == 1) printf("%d ", mat[i][j-1]);
				k = 1;
			}
		}
		printf("\n");
		k = 1;
	}
	//===============================================


	for(i = 0; i < row; i++) free(mat[i]);
	free(mat);
	return 0;
}

