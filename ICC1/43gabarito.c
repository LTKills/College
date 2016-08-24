/*
 * =====================================================================================
 *
 *       Filename:  43gabarito.c
 *
 *    Description:  Correção de Gabarito
 *
 *        Version:  1.0
 *        Created:  04/28/16 19:16:31
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

int main(int argc, char *argv[]){
	int questoes, alunos, i, j;
	char *gab = NULL;
	float *media = NULL;
	char *atual = NULL;

	scanf("%d %d", &questoes, &alunos);

	media = (float*) calloc(alunos, sizeof(float));			//	callocando, porque malloc eh pros fracos!
	gab = (char*) calloc(questoes+1, sizeof(char));
	atual = (char*) calloc(questoes+1, sizeof(char));

	//	lendo gabarito
		scanf("%s", gab);

	//	conferindo acertos
	for(i = 0; i < alunos; i++){
		scanf("%s", atual);		//	nao colocar &atual, pois dah seg fault!!!
		for(j = 0; j < questoes; j++){
			if(atual[j] == gab[j]) media[i]++;
		}
		media[i] /=  questoes;
	}
	//	imprimindo medias em ordem
	for(i = 0; i < alunos; i++){
		printf("%.2f\n", media[i]*10); //	nao esquecer de multiplicar a media por 10
	}


	//	liberando geral
	free(media);
	free(gab);
	free(atual);
	return 0;
}














