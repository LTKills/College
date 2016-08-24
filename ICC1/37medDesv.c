/*
 * =====================================================================================
 *
 *       Filename:  37medDesv.c
 *
 *    Description:  Mádia aritmética e Desvio padrão
 *
 *        Version:  1.0
 *        Created:  04/23/16 19:01:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: LTKills
 *   Organization: The University of Sao Paulo
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main(int argc, char *argv[]){
	int n, i;
	double k, devPad, media = 0;
	double *vec =  NULL;
	scanf("%d", &n);

	vec = (double*) malloc(sizeof(double)*n);

	for(i = 0; i < n; i++){
		scanf("%lf", &vec[i]);
		media += vec[i];
	}
	media /= n;
	printf("%.4lf\n", media);

	for(i = 0; i < n; i++){
		devPad += pow(vec[i]-media, 2);
	}


	printf("%.4lf\n", sqrt(devPad/n));

	return 0;
}










