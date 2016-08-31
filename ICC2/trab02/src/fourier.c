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
#include <stdlib.h>
#include <stdio.h>
#include <file.h>
#include <complex.h>
#include <math.h>


#define SIZE UNSIGNED_CHAR

double complex *inductGen(unsigned char *raw, int N){
	int k, t, n;
	double complex *inducts = malloc(sizeof(double)*N);
	double x, pi = M_PI;
	double complex z, sum;

	for(k = 0; k < N; k++){

		sum = 0;

		for(t = 0; t < N/2; t++){
			x = k*2*pi*t/N;
			sum += cexp(-I*x);
		}

		if(k == 0)
			inducts[k] = (1.0/N)*raw[k]*sum;
		else
			inducts[k] = (2.0/N)*raw[k]*sum;

	}
	return inducts;
}

int *magsDecrease(int *induct, int size){

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
	mags = magsDecrease(induct, size);


	free(vec);
	fclose(fp);
	return 0;
}

