/*
 * =====================================================================================
 *
 *       Filename:  68jacLucas.c
 *
 *    Description:  Sequência Jacobsthal Lucas
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

double *tetranacci(int n){
	int i;
	double *vec;
	vec = malloc(sizeof(double)*n);
	vec[0] = 2;
	vec[1] = 1;

	for(i = 2; i < n; i++)
		vec[i] = vec[i-1] + 2*vec[i-2];
	return vec;
}

double media(double *tre, int n){
	int i;
	double av = 0;

	for(i = 0; i < n; i++ )
		av += tre[i];


	return av/n;
}

double var(double *tre, int n, double av){
	int i;
	double v = 0;

	for(i = 0; i < n; i++)
		v += pow((tre[i]-av), 2);

	return v/n;

}

double chebyshev(double *tre, int n){
	int i;
	double max = 0;

	for(i = 0; i < n/2; i++)
		if(abs(tre[i] - tre[i + n/2]) > max)
			max = abs(tre[i] - tre[i + n/2]);

	return max;
}

int main(int argc, char *argv[]){
	int opt, n, i;
	double *tre;

	scanf("%d %d", &opt, &n);
	tre = tetranacci(n);

	switch(opt){
		case 1:
			for(i = 0; i < n; i++)
				printf("%.1f ", tre[i]);
			printf("\n");
			break;

		case 2:
			printf("%.4lf\n", var(tre, n, media(tre, n)));
			break;

		case 3:
			printf("%.4lf\n", chebyshev(tre, n));
			break;
	}


	free(tre);
	return 0;
}
