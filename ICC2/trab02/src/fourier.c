/*
 * =====================================================================================
 *
 *       Filename:  fourier.c
 *
 *    Description:  Fourier Transform for Noise Removing on Audio Files
 *
 *        Version:  1.0
 *        Created:  08/24/2016 12:52:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  USP
 *
 * =====================================================================================
 */

#define SIZE UNSIGNED_CHAR


#include <stdlib.h>
#include <stdio.h>
#include <file.h>
#include <complex.h>
#include <math.h>



double complex *inductGen(unsigned char *raw, int N){
	int k, t;
	double complex *inducts = malloc(sizeof(double complex)*N);
	double x, pi = M_PI;
	double complex z;

	for(k = 0; k < N; k++){
		z = 0;
		for(t = 0; t < N/2; t++){
			x = k * 2 * pi * t / N;
			//z += cexp(x);
			z += sin(x) + I*cos(x);
		}

		if(k == 0)
			inducts[k] = (1.0/N)*raw[k]/z;
		else
			inducts[k] = (2.0/N)*raw[k]/z;

	}
	return inducts;
}

double complex *magsDecrease(double *induct, int size){

}


int main(int argc, char *argv[]){
	char *file;
	unsigned char *raw;
	int c, size, i;
	double complex *inducts, *mags;
	FILE *fp;

	file = readLine(stdin);
	fp = fopen(file, "rb");
	free(file);
	scanf("%d", &c);

	raw = (unsigned char*)readFile(fp, SIZE, &size);

	inducts = inductGen(raw, size);
	//mags = magsDecrease(inducts, size);

	/*Simply testing*/
	for(i = 0; i < size; i++){
		printf("R=%lf\tIm=%lf\n", creal(inducts[i]), cimag(inducts[i]));
	}


	free(inducts);
	//free(mags);
	fclose(fp);
	return 0;
}

