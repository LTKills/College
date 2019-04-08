#include <stdlib.h>
#include <stdio.h>

/*Prints matrix*/
void matrixPrint(int **matrix, int row, int col){
	int i, j;
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

/*Frees previously allocated matrix*/
void matrixFree(int **matrix, int row){
	int i;
	for(i = 0; i < row; i++) free(matrix[i]);
	free(matrix);
}

/*Creates empty matrix*/
int **matrixCreate(int row, int col){
	int i;
	int **matrix;

	matrix = (int **) calloc(row, sizeof(int *));
	for(i = 0; i < row; i++)
		matrix[i] = (int *) calloc(col, sizeof(int));

	return matrix;
}

int **matrixCopy(int **src, int row, int col) {
	int i, j;
	int **dest;
	dest = matrixCreate(row, col);

	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			dest[i][j] = src[i][j];
		}
	}
	return dest;
}

/*Returns matrix read from file pointed by fp*/
int **matrixReadFile(FILE *fp, int row, int col){
	int i, j;
	int **matrix;
	matrix = matrixCreate(row, col);

	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
			fscanf(fp, "%d", &matrix[i][j]);

	return matrix;
}

/* Simple matrix convolution operation */
void convolution(int **matrix, int **big, int row, int col, int **mask, int maskDim) {
	int i, j, l, k;
	int d = maskDim/2, value = 0;

	for(i = d; i < row+d; i++) {
		for(j = d, value = 0; j < col+d; j++, value = 0) {
			/*Apply the mask*/
			 for(k = 0; k < maskDim; k++) {
				 for(l = 0; l < maskDim; l++) {
					value += (mask[k][l] * matrix[i-d+k][j-d+l]);		// multiplying values
				}													//	^^tricky counters^^
			}
			big[i][j] = value;
			/*Move to next element*/
		}
	}
}

int ***readMasks(int nMasks, int dim) {
	int ***masks, i, j, k;

	masks = (int ***) malloc(sizeof(int **) * nMasks);
	for(k = 0; k < nMasks; k++) { 	// for each mask
		masks[k] = matrixCreate(dim, dim);
		for(i = 0; i < dim; i++) {
			for(j = 0; j < dim; j++) {
				scanf("%d", &masks[k][i][j]);
			}
		}
	}

	return masks;
}

/*Printing all masks*/
void printMasks(int ***masks, int nMasks, int dim){
	int k;

	for(k = 0; k < nMasks; k++){
		printf("\n\nNEWMASK\n\n");
		matrixPrint(masks[k], dim, dim);
	}
}

/*Frees masks' vector*/
void freeMasks(int ***masks, int nMasks, int dim){
	int k;
	for(k = 0; k < nMasks; k++){
		matrixFree(masks[k], dim);
	}
	free(masks);
}
