/*
 * =====================================================================================
 *
 *       Filename:  38div.c
 *
 *    Description:  Divisão por subtração
 *
 *        Version:  1.0
 *        Created:  04/23/16 22:58:50
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


int main(int argc, char *argv[]){
	int i, a, b;
	scanf("%d %d", &a, &b);

	while(a >= b){
		a -= b;
		i++;
	}

	printf("%d\n%d\n", i, a);

	return 0;
}



