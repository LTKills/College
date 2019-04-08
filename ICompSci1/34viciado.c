/*
 * =====================================================================================
 *
 *       Filename:  34viciado.c
 *
 *    Description:  Dado Viciado
 *
 *        Version:  1.0
 *        Created:  04/25/16 23:31:47
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



int main(int argc, char *argv[]){
	int dado[6];
	int atual, i, k, maior = INT_MIN;

	//zerando o vetor dado
	for(i = 0; i < 6; i++){
		dado[i] = 0;
	}

	// contando ocorrencias
	while(scanf("%d", &atual) != EOF){
		dado[atual-1]++;
	}


	// imprimindo a face mais frequente (apenas uma)
	for(i = 0; i < 6; i++){
		if(dado[i] > maior){
			maior = dado[i];
			k = i+1;	// i começa em zero, nao existe face zero
		}
	}
	printf("%d\n", k);

	// tratando o caso em que há mais de uma moda
	// o for anterior pegou a moda baeado na menor face
	// assim, caso a moda se repita, ela será sempre
	// de uma face maior do que a já registrada
	for(i = 0; i < 6; i++){
		if(maior == dado[i] && k-1 < i){
			printf("%d\n", i+1);
		}
	}

	printf("%d\n", maior);



	return 0;
}


