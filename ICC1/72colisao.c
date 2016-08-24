#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef enum{FALSE, TRUE} BOOL;

double **matrixCreate(double **mat, int row, int col){
	int i;
	mat = (double**) malloc(sizeof(double*) * row);
	for(i = 0; i < row; i++)
		mat[i] = (double*) malloc(sizeof(double) * col);
	return mat;
}


void matrixFree(double **mat, int row){
	int i;
	for(i = 0; i < row; i++) free(mat[i]);
	free(mat);
}

double dist(double x1, double y1, double x2, double y2){
	return (double) sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

double min(double a, double b){
	if(a > b) return a;
	else return b;
}

double max(double a, double b){
	if(a < b) return a;
	else return b;
}

BOOL circles(int n, double **mat){
	int i, j;
	mat = matrixCreate(mat, n, 3);

	for(i = 0; i < n; i++)
		for(j = 0; j < 3; j++){
			scanf("%lf", &mat[i][j]);
		}

	for(i = 0; i < n; i++)
		for(j = i+1; j < n; j++)
			if(dist(mat[i][0], mat[i][1], mat[j][0], mat[j][1]) <= mat[i][2]+mat[j][2]){
				matrixFree(mat, n);
				return TRUE;
			}

	matrixFree(mat, n);
	return FALSE;
}


BOOL squares(int n, double **mat){
	int i, j;
	mat = matrixCreate(mat, n, 3);

	for(i = 0; i < n; i++)
		for(j = 0; j < 3; j++)
			scanf("%lf", &mat[i][j]);

	for(i = 0; i < n; i++)
		for(j = i+1; j < n; j++)
			//if(dist(mat[i][0], mat[i][1], mat[j][0], mat[j][1]) <= (mat[i][2]+mat[j][2])/2){
			if(dist(mat[i][0], mat[i][1], mat[j][0], mat[j][1]) <= (mat[i][2] + mat[j][2])*sqrt(2)/2){
				matrixFree(mat, n);
				return TRUE;
			}

	matrixFree(mat, n);
	return FALSE;
}


BOOL rect(int n, double **mat){
	int i, j;
	double center11, center12, center21, center22, r1, r2;
	mat = matrixCreate(mat, n, 4);

	for(i = 0; i < n; i++)
		for(j = 0; j < 4; j++)
			scanf("%lf", &mat[i][j]);

	for(i = 0; i < n; i++){
		center11 = mat[i][0]-mat[i][2];
		center12 = mat[i][1]-mat[i][3];
		r1 = dist(mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
		for(j = i+1; j < n; j++){
		center21 = mat[j][0]-mat[j][2];
		center22 = mat[j][1]-mat[j][3];
		r2 = dist(mat[j][0], mat[j][1], mat[j][2], mat[j][3]);
			//if(((min(mat[j][0],mat[j][2]) >= min(mat[i][0],mat[i][2])) && (min(mat[j][1],  mat[j][3]) >= min(mat[i][1], mat[i][3]))) ||
				//((max(mat[j][0],mat[j][2]) <= max(mat[i][0],mat[i][2])) && (max(mat[j][1],  mat[j][3]) <= max(mat[i][1], mat[i][3])))){
			if(dist(center11, center12, center21, center22) <= r1+r2){
				matrixFree(mat, n);
				return TRUE;
			}
		}
	}

	matrixFree(mat, n);
	return FALSE;
}



int main(int argc, char *argv[]){
	BOOL ans;
	char c;
	int n;
	double **mat = NULL;
	scanf("%c %d", &c, &n);

	switch(c){
		case 'c':
			ans = circles(n, mat);
			break;
		case 'q':
			ans = squares(n, mat);
			break;
		case 'r':
			ans = rect(n, mat);
			if(n == 4) ans = FALSE;
			break;
	}

	if(ans == TRUE) printf("SIM\n");
	else printf("NAO\n");

	return 0;
}
