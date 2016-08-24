/*
 * =====================================================================================
 *
 *       Filename:  67tetranacci.c
 *
 *    Description:  Tetranacci
 *
 *        Version:  1.0
 *        Created:  06/22/16 15:36:37
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

float *tetranacci(int n){
	int i;
	float *vec;
	vec = malloc(sizeof(float)*n);
	vec[0] = 0;
	vec[1] = 0;
	vec[2] = 1;
	vec[3] = 1;

	for(i = 4; i < n; i++)
		vec[i] = vec[i-1] + vec[i-2] + vec[i-3] + vec[i-4];
	return vec;
}

double media(float *tre, int n){
	int i;
	double av = 0;

	for(i = 0; i < n; i++ )
		av += pow(tre[i], 2);


	return sqrt(av/n);
}

double manhattan(float *tre, int n){
	int i;
	double sum = 0;

	for(i = 0; i < n/2; i++)
		sum += abs(tre[i] - tre[i+n/2]);

	return sum;
}

int main(int argc, char *argv[]){
	int opt, n, i;
	float *tre;

	scanf("%d %d", &opt, &n);
	tre = tetranacci(n);

	switch(opt){
		case 1:
			for(i = 0; i < n; i++)
				printf("%.1f ", tre[i]);
			printf("\n");
			break;

		case 2:
			printf("%.4lf\n", media(tre, n));
			break;

		case 3:
			printf("%.4lf\n", manhattan(tre, n));
			break;
	}


	free(tre);
	return 0;
}
