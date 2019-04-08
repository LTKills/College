/*
 * =====================================================================================
 *
 *       Filename:  mmc.c
 *
 *    Description:  Minimo multiplo comum
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

int testMult(int a, int b, int mult, int i){

	if(mult % a == 0)			//	se b for divisivel por a, retorne b como minimo
		return mult;

	mult = b * i;

	mult = testMult(a, b, mult, ++i);							//	senao, chame a funcao

	return mult;

}



int main(void){
	int a, b;

	scanf("%d %d", &a, &b);

	if(a == 1){					//	tratando excecoes
		printf("%d\n", b);
		return 0;
	}else if(b == 1){
		printf("%d\n", a);
		return 0;
	}

	printf("%d\n", testMult(a, b, b, 1));			//	chamando a funcao recursiva testMult

	return 0;
}



