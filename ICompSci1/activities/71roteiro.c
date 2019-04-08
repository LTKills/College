/*
 * =====================================================================================
 *
 *       Filename:  71roteiro.c
 *
 *    Description:  Roteiro de Viagem
 *
 *        Version:  1.0
 *        Created:  06/29/16 17:25:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKIlls
 *   Organization:  USP
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>




int main(void){
	int i, j, n;
	scanf("%d", &n);
	char org[3], dest[3], mat1[n][3], mat2[n][3];

	for(i = 0; i < n; i++)
		scanf("%s %s", mat1[i], mat2[i]);
	scanf("%s %s", org, dest);
	return 0;
}

