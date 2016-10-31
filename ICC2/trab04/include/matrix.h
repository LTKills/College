#ifndef _MATRIX_H_
#define _MATRIX_H_

void matrixPrint(int **matrix, int row, int col);
void matrixFree(int **matrix, int row);
int  **matrixCreate(int row, int col);
int **matrixCopy(int **src, int row, int col);
int **matrixReadFile(FILE *fp, int row, int col);
void convolution(int **matrix, int **big, int row, int col, int **mask, int maskDim);
int ***readMasks(int nMasks, int dim);
void freeMasks(int ***masks, int nMasks, int dim);
void printMasks(int ***masks, int nMasks, int dim);


#endif
