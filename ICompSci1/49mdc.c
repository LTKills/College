/*
 * =====================================================================================
 *
 *       Filename:  49mdc.c
 *
 *    Description:  Maximo divisor comum
 *
 *        Version:  1.0
 *        Created:  04/30/16 13:07:34
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

int testDiv(int a, int b){		// funcao que calcula o mdc recursivamente
	int r;
	if(a % b == 0)
		return b;

	r = a % b; 			//	A recebe B e B recebe A mod B
	a = b;				//	R eh a variavel auxiliar
	b = r;
	r = testDiv(a , b);
	return r;
}


int main(void){
	int a, b;

	scanf("%d %d", &a, &b);

	if(a == 1){					//	tratando excecoes
		printf("%d\n", 1);
		return 0;
	}else if(b == 1){
		printf("%d\n", 1);
		return 0;
	}

	if(b > a)
		printf("%d\n", testDiv(b, a));			//	chamando a funcao recursiva testDiv

	else if(a > b)
		printf("%d\n", testDiv(a ,b));			//	chamando a funcao recursiva testDiv
	else
		printf("%d\n", a);

	return 0;
}


