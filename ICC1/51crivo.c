/*
 * =====================================================================================
 *
 *       Filename:  51erastotenes.c
 *
 *    Description:  Crivo de Erastotenes
 *
 *        Version:  1.0
 *        Created:  05/21/2016 04:56:16 PM
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

int isprime(int num){
	int i, k = 0;
	for(i = 1; i <= num; i++)
		if(num%i == 0)
			k++;
	if(k > 2) return 1;		//	nao eh primo
	return 0;				//	eh primo
}

int main(int argc, char *argv[]){
	int i, j, k, l;
	int *vec;
	scanf("%d", &k);

	l = (int) floor(sqrt(k));

	vec = (int *) malloc(sizeof(int)*(k-1));

	for(i = 0; i < k-1; i++) vec[i] = i+2;		//	preenche o vetor dos numeros
	for(i = 0; i < k-1; i++) printf("%d ", vec[i]);		//	imprime o vetor dos numeros
	printf("\n");

	for(i = 2; i <= l; i++){
		if(isprime(i) != 0)		//	se nao for primo
			continue;
		for(j = i-2; j < k-1; j++)			//	retirando multiplos
			if(vec[j] % i == 0 && vec[j] != i) vec[j] = -1;

		for(j = 0; j < k-1; j++)					//	imprime tudo
			if(vec[j] != -1) printf("%d ", vec[j]);
		printf("\n");
	}



	return 0;
}

