/*
 * =====================================================================================
 *
 *       Filename:  trab04.c
 *
 *    Description:  Trabalho 4
 *
 *        Version:  1.0
 *        Created:  05/24/16 23:02:17
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
#include <limits.h>
#include <math.h>

#define	NEGATIVE 1		//	Operador 1 -> negativo
#define CONVOLUTION 2	//	Operador 2 -> convolucao
#define ENTER 10

char *readLine(FILE *fp){			//	leitura e alocação dinamica de strings
	char *string = NULL;
	char c;
	int i = 0;

	do{
		string = (char *) realloc(string, sizeof(char)*(i+1));
		fscanf(fp, "%c", &c);
		string[i++] = c;
	}while(c != ENTER);
	string[i-1] = '\0';

	return string;
}

void matrixFree(double **matrix, int row){			//	libera matriz de row linhas
	int i;
	for(i = 0; i < row; i++) free(matrix[i]);
	free(matrix);
}

double **matrixCreate(int row, int col){			//	cria matriz de row linhas e col colunas
	int i;
	double **matrix;

	matrix = (double **) calloc(sizeof(double*), row);
	for(i = 0; i < row; i++)
		matrix[i] = (double *) calloc(sizeof(double), col);

	return matrix;
}

double **matrixReadFile(FILE *fp, int row, int col){			//	le uma matrix row X col a partir de um arquivo dado
	int i, j;
	double **matrix;
	matrix = matrixCreate(row, col);

	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
			fscanf(fp, "%lf", &matrix[i][j]);

	return matrix;
}

void convolution(double **matrix, int row, int col, double **mask, int maskDim){			//	realiza os produtos da convolução com a máscara desejada
	int i, j, l, k;
	int d = maskDim/2, value = 0;
	double **big;
	big = matrixCreate(row + d*2, col + d*2);		//	criando e zerando a maior matriz
	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
			big[i+d][j+d] = matrix[i][j];		//	repassando matrix para big

	for(i = d; i < row+d; i++){
		for(j = d, value = 0; j < col+d; j++, value = 0){
			 for(k = 0; k < maskDim; k++){
				 for(l = 0; l < maskDim; l++){
					value += (mask[k][l] * big[i+d-k][j+d-l]);		//	multiplicando os valores
				}													//	^^tricky contadores^^
			}
			matrix[i-d][j-d] = value;
		}
	}
	matrixFree(big, row + d*2);
}

void normalizer(double **matrix, int row, int col, double maxValue){				//	normaliza matrix "corretamente""
	double max = matrix[0][0], min = matrix[0][0];									//	(zueira mellão, tá tudo nos trinques :D)
	int i, j;
	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++){
			if(matrix[i][j] > max) max = matrix[i][j];
			if(matrix[i][j] < min) min = matrix[i][j];
		}

	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
			matrix[i][j] = maxValue*((matrix[i][j] - min)/(max-min));
}

int main(int argc, char *argv[]){
	int i, j, k, row, col, op, maskDim;			//MDOV => massive declaration of variables
	double **matrix, **mask, maxValue;
	FILE *fp, *fp2;
	char *imgName = NULL, *type = NULL, *imgMask = NULL, c;

	scanf("%d", &op);								//	recebe o operador
	fgetc(stdin);
	imgName = readLine(stdin);						//	le o nome do arquivo imagem a ser aberto

	if(op == CONVOLUTION){
		imgMask = readLine(stdin);							//	recebe o nome do arquivo da mascara
		fp2 = fopen(imgMask, "r");							//	abre a mascara
		fscanf(fp2, "%d", &maskDim);
		mask = matrixReadFile(fp2, maskDim, maskDim);
	}

	fp = fopen(imgName, "r");		//	abre a imagem

	type = readLine(fp);			//	le o tipo da imagem
	c = fgetc(fp);
	if(c == '#'){
		while(c != '\n'){
			c = fgetc(fp);
		}
	}else
		fseek(fp, -1, SEEK_CUR);

	fscanf(fp, "%d %d", &col, &row);	//	le as dimensoes da matriz
	fscanf(fp, "%lf", &maxValue);		// le o valor maximo dos pixels
	matrix = matrixReadFile(fp, row, col);

	switch(op){
		case NEGATIVE:
			for(i = 0; i < row; i++)
				for(j = 0; j < col; j++)
					matrix[i][j] = maxValue - matrix[i][j];
			break;

		case CONVOLUTION:
			convolution(matrix, row, col, mask, maskDim);
			normalizer (matrix, row, col, maxValue);
			break;

		default:
			printf("Invalid operator\n");
			return 1;
	}

	printf("%s\n", type);						//	imprimindo resultados
	printf("%d %d\n", col, row);
	printf("%d\n", (int) maxValue);
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			printf("%d ", (int) round(matrix[i][j]));
		}
		printf("\n");
	}

	if(op == CONVOLUTION){						//	libera geral
		fclose(fp2);
		matrixFree(mask, maskDim);
		free(imgMask);
	}
	free(type);
	free(imgName);
	matrixFree(matrix, row);
	fclose(fp);
	return 0;
}
