/*
 * =====================================================================================
 *
 *       Filename:  41vendas.c
 *
 *    Description:  Melhor dia de vendas
 *
 *        Version:  1.0
 *        Created:  04/28/16 16:04:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:	USP
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>




int main(int argc, char *argv[]){
	int sell[31], i;
	int max = INT_MIN;

	// lendo a quantidade de vendas
	for(i = 0; i < 31; i++){
		scanf("%d", &sell[i]);
	}

	//calculando o valor máximo

	for(i = 0; i < 31; i++){
		if(sell[i] > max)
			max = sell[i];
	}

	printf("%d\n", max);

	//imprimindo o(s) dia(s) de mais vendas
	for(i = 0; i < 31; i++){
		if(sell[i] == max)
			printf("%d\n", (i+1));
	}

	return 0;
}




