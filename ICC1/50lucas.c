/*
 * =====================================================================================
 *
 *       Filename:  50lucas.c
 *
 *    Description:  Sequencia de Lucas
 *
 *        Version:  1.0
 *        Created:  05/01/16 17:28:31
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

int fibonacciHu3(int n, int p, int q){	//	P eh o numero mais distante do atual, Q o menos distante
	if(n == 3)
		return 3;
	if(n == 2)
		return 1;
	q = fibonacciHu3(n-1, q, p);		// chamando recursivamente fibonacci (porque essa budega eh fibonacci, nao me diga o contrario!)
	p = fibonacciHu3(n-2, q, p);		// chamando esse troço novamente
	return p+q;
}



int main(int argc, char *argv[]){
	int n;

	scanf("%d", &n);			//	lendo quantidade de numeros
	if(n == 1){					//	tratando excecoes
		printf("%d\n", 2);
		return 0;
	}else if(n == 2){
		printf("%d\n", 1);
		return 0;
	}

	printf("%d.000000\n", fibonacciHu3(n+1, 2, 1));	//	calculando e imprimindo "lucas" (coff fibonacci! coff...)
		//		^^^^
			//gambiarra, admito, hehe...
	return 0;
}




