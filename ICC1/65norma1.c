/*
 * =====================================================================================
 *
 *       Filename:  65norma1.c
 *
 *    Description:  Norma 1
 *
 *        Version:  1.0
 *        Created:  06/22/16 21:36:42
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


int main(int argc, char *argv[]){
	FILE *fp1, *fp2;
	int row, j, k;
	double **matA, **matB, sum1 = 0, sum2 = 0, max2 = 0, max1 = 0, a;
	char name1[20], name2[20], c = 0;
	scanf("%s %s", name1, name2);

	fp1 = fopen(name1, "r");
	fp2 = fopen(name2, "r");

	// Checando as dimensões
	for(row = 0; c != '\n'; row++){
		fscanf(fp1, "%lf", &a);
		fscanf(fp1, "%c", &c);
	}
	fseek(fp1, 0, SEEK_SET);

	// Criando as matrizes A e B
	matA = (double**) calloc(row, sizeof(double*));
	matB = (double**) calloc(row, sizeof(double*));
	for(j = 0; j < row; j++){
		matA[j] = (double*) calloc(row, sizeof(double));
		matB[j] = (double*) calloc(row, sizeof(double));
	}

	// Lendo as matrizes
	for(j = 0; j < row; j++){
		for(k = 0; k < row; k++){
			fscanf(fp1, "%lf", &matA[j][k]);
			fscanf(fp2, "%lf", &matB[j][k]);
		}
	}

	// Norma 1
	for(k = 0; k < row; k++){
		for(j = 0; j < row; j++){
			sum1 += fabs(matA[j][k]);
			sum2 += fabs(matB[j][k]);
		}
		if(max1 < sum1) max1 = sum1;
		if(max2 < sum2) max2 = sum2;
		sum1 = 0;
		sum2 = 0;
	}

	printf("%.4lf\n%.4lf\n", max1, max2);

	for(j = 0; j < row; j++){
		for(k = 0; k < row; k++){
			printf("%.4lf ", (matA[j][k]+matB[j][k]));
			matB[j][k] += matA[j][k];
		}
		printf("\n");
	}
	// Norma 1 da matriz soma
	for(k = 0; k < row; k++){
		for(j = 0; j < row; j++){
			sum2 += fabs(matB[j][k]);
		}
		if(max2 < sum2) max2 = sum2;
		sum2 = 0;
	}
	printf("%.4lf\n", max2);

	fclose(fp1);
	fclose(fp2);
	for(j = 0; j < row; j++){
		free(matA[j]);
		free(matB[j]);
	}
	free(matA);
	free(matB);

	return 0;
}
