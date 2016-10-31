/*
 * =====================================================================================
 *
 *       Filename:  learning.c
 *
 *    Description:  Machine Learning using K-nearest neightboors
 *
 *        Version:  1.0
 *        Created:  10/07/2016 02:25:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  The University of Sao Paulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <file.h>
#include <learning.h>
#include <matrix.h>

int main(int argc, char *argv[]) {

	FILE *ftrain, *fclass, *ftest;
	char *training, *class, *test, *img, *aux;
	int i, nMasks = 0, maskDim, ***masks, kNearest, nimgs, dim = 0;
	double **trainVec = NULL, *testVec = NULL;
	int *nearest, *classes, *neigh, max = 0, maxPos = 0;

	/*Reading inputs*/
	training = readLine(stdin);
	class = readLine(stdin);
	test = readLine(stdin);

	scanf("%d", &nMasks);
	scanf("%d", &maskDim);

	// Reading masks
	masks = readMasks(nMasks, maskDim);
	scanf("%d", &kNearest); 				// k-nearest neightboors
	/*Inputs read*/


	/*=======TRAINING=======*/
	ftrain = fopen(training, "r");
	for(nimgs = 0; !feof(ftrain); nimgs++) {
		img = readLine(ftrain); // pick an image

		// Creates one more space for training vector
		trainVec = (double **) realloc(trainVec, sizeof(double *) * (nimgs+1));

		// generates feature vector for the image
		trainVec[nimgs] = train(img, masks, maskDim, nMasks, &dim);

		free(img);
		fgetc(ftrain);
		if(feof(ftrain)) break; // end of file
		fseek(ftrain, -1, SEEK_CUR);
	}
	nimgs++;
	/*====================*/

	/*=======CLASSIFYING=======*/
	ftest = fopen(test, "r");
	fclass = fopen(class, "r");

	classes = (int *) malloc(sizeof(int) * nimgs);
	neigh = (int *) calloc(nimgs, sizeof(int));

	for(i = 0; i < nimgs; i++)
		fscanf(fclass, "%d", &classes[i]);

	while(!feof(ftest)) {
		maxPos = -1;
		max = INT_MIN;
		img = readLine(ftest);

		// receives testing img
		testVec = train(img, masks, maskDim, nMasks, &dim); // generate feature vector for testing image
		nearest = k_nearest_neightboors(kNearest, testVec, trainVec, nimgs, nMasks*6*dim); // generate the nearest neightboors' vector

		for(i = 0; i < kNearest; i++) {
			neigh[classes[nearest[i]]]++;
		}

		for(i = 0; i < nimgs; i++) {
			if(neigh[i] > max) {
				max = neigh[i];
				maxPos = i;
			}
			neigh[i] = 0;
		}
		printf("%d.000\n", maxPos);

		free(img);
		free(nearest);
		free(testVec);
		fgetc(ftest);
		if(feof(ftest)) break;
		fseek(ftest, -1, SEEK_CUR);
	}
	/*=========================*/




	fclose(ftrain);
	fclose(fclass);
	fclose(ftest);
	freeMasks(masks, nMasks, maskDim);
	for(i = 0; i < nimgs; i++) free(trainVec[i]);
	free(trainVec);
	free(test);
	free(class);
	free(classes);
	free(neigh);
	free(training);

	return 0;
}

