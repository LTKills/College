/*
 * =====================================================================================
 *
 *       Filename:  58contagem.c
 *
 *    Description:  Contagem de Caracteres
 *
 *        Version:  1.0
 *        Created:  05/22/16 12:36:34
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

int main(void){
	FILE *fp;
	char nome[20];
	scanf("%s", nome);
	fp = fopen(nome, "r");

	fseek(fp, 0 ,SEEK_END);
	printf("%d\n", (int) ftell(fp));

	fclose(fp);
	return 0;
}

