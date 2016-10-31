#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <file.h>
#include <matrix.h>
#include <learning.h>

/* Generating feature vector */
void vecGen(double *vec, int n, int **mat, int dim, int d) {
	int i, j;
	double av = 0, var = 0, e = 0;
	int pos = 0, z = 0, neg = 0;


	for(i = d; i < (dim+d); i++) {

		for(j = d; j < (dim+d); j++) {
			av += mat[i][j];
			e += mat[i][j]*(log(abs(mat[i][j])+1)/log(2)); // entropy
			if(mat[i][j] > 0) pos++; // positive
			else if(mat[i][j] == 0) z++; // zeroes
			else if(mat[i][j] < 0) neg++; // negative
		}


		for(j = d; j < (dim+d); j++) //variance
			var += (mat[i][j]-(av/dim))*(mat[i][j]-(av/dim)); 	//variance

		vec[n+(i-1)*6+0] = pos;	 // positives
		vec[n+(i-1)*6+1] = z;	 // zeroes
		vec[n+(i-1)*6+2] = neg;	 // negatives
		vec[n+(i-1)*6+3] = av/dim; // average
		vec[n+(i-1)*6+4] = var/dim; // variance
		vec[n+(i-1)*6+5] = -e;	 // entropy

		pos = 0;
		z = 0;
		neg = 0;
		av = 0;
		var = 0;
		e = 0;
	}
}

/* Applies all the masks into img and generates the feature vector :D */
double *train(char *img, int ***masks, int maskDim, int nMasks, int *dim) {
	char *type;
	unsigned char *aux;
	double *trainVec = NULL;
	FILE *fimg;
	int maxColors, i, j, **mat = NULL, **auxMat = NULL;
	int d = maskDim/2;

	fimg = fopen(img, "r+");

	type = readLine(fimg); // Img type (always the same...)
	fscanf(fimg, "%d %d", dim, dim);	// both dimentions are equal
	fscanf(fimg, "%d", &maxColors); // It is always 255, but... (my code, my rules)

	// Allocating for img matrix
	mat = (int **) calloc((*dim) + (2 * d), sizeof(int *));
	for(i = 0; i < (*dim)+2*d; i++)
		mat[i] = (int *) calloc((*dim) + (2 * d), sizeof(int));


	aux = (unsigned char *) malloc(sizeof(unsigned char) * (*dim)); // aux is one line

	for(i = 0; i < (*dim); i++) {
	   	fread(aux, sizeof(unsigned char), (*dim), fimg); // Reading each line
		for(j = 0; j < (*dim); j++) {
			/*Fill the borders with zeroes for convolution*/
			mat[i+d][j+d] = (int) aux[j];
			/*The rest is just copied to the matrix*/
		}
	}


	/*Generating feature vector*/
	trainVec = (double *) calloc(nMasks*(*dim)*6, sizeof(double));

	for(i = 0; i < nMasks; i++) {
		auxMat = matrixCopy(mat, (*dim) + (2 * d), (*dim) + (2 * d)); // preserve the original image
		convolution(mat, auxMat, (*dim), (*dim), masks[i], maskDim);
		vecGen(trainVec, i*6*(*dim), auxMat, (*dim), d);
		matrixFree(auxMat, (*dim)+(2*d));
	}


	fclose(fimg);
	free(aux);
	free(type);
	matrixFree(mat, ((*dim)+2*d));
	return trainVec;
}



struct NEAR {
	double dist;
	int pos;
};

void swap(struct NEAR *nearest, int a, int b) {
	struct NEAR aux;

	aux.dist = nearest[a].dist;
	aux.pos = nearest[a].pos;

	nearest[a].dist = nearest[b].dist;
	nearest[a].pos = nearest[b].pos;

	nearest[b].dist = aux.dist;
	nearest[b].pos = aux.pos;

}


/* Returns the positions of the k-nearest neightboors */
int *k_nearest_neightboors(int kNearest, double *test, double **trainVec, int nimgs, int line) {

	struct NEAR *near = (struct NEAR *) malloc(sizeof(struct NEAR) * nimgs);
	int *nearest = (int *) malloc(sizeof(int) * kNearest);
	int i, j;

	for(i = 0; i < nimgs; i++) {
		near[i].dist = euclidean_distance(test, trainVec[i], line);
		near[i].pos = i;
	}

	/* Ascending order (least distant) */
	for(i = 0; i < nimgs; i++)
		for(j = 0; j < nimgs-i-1; j++)
			if(near[j].dist > near[j+1].dist) swap(near, j, j+1);

	for(i = 0; i < kNearest; i++)
		nearest[i] = near[i].pos;

	free(near);

	return nearest;

}

