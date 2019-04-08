/*
 * =====================================================================================
 *
 *       Filename:  63tribonacci.c
 *
 *    Description:  Tribonacci
 *
 *        Version:  1.0
 *        Created:  06/22/16 14:54:03
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

double media(int start, float *vec, int end){
	int i;
	double av = 0;

	for(i = start; i < end; i++)
		av += vec[i];

	return av/(end-start);
}

float *tribonacci(int n){
	int i;
	float *vec = NULL;
	vec = malloc(sizeof(float)*n);
	vec[0] = 0;
	vec[1] = 0;
	vec[2] = 1;

	for(i = 3; i < n; i++)
		vec[i] = vec[i-3] + vec[i-2] + vec[i-1];

	return vec;
}

double cov(int n, float *vec, double av, double av2){
	int i;
	double value = 0;

	for(i = 0; i < n/2; i++)
		value += (vec[i]-av)*(vec[i+n/2]-av2);

	return value;
}

double var(int start, float *vec, int end, double av){
	int i;
	double sum = 0;

	for(i = start; i < end; i++)
		sum += (vec[i]-av)*(vec[i]-av);

	return sum;
}

int main(int argc, char *argv[]){
	int opt, n, i;
	float *tri;
	double av, av2, result;
	scanf("%d %d", &opt, &n);

	tri = tribonacci(n);
	switch(opt){
		case 1:
			for(i = 0; i < n; i++)
				printf("%.1f ", tri[i]);
			printf("\n");

			break;

		case 2:
			av = media(0, tri, n);
			printf("%.4lf\n", av);

			break;

		case 3:
			av = media(0, tri, n/2);
			av2 = media(n/2, tri, n);
			result = (cov(n, tri, av, av2)/sqrt(var(0, tri, n/2, av)*var(n/2, tri, n, av2)));
			printf("%.4lf\n", result);

			break;
	}
	return 0;
}


