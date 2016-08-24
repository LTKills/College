/*
 * =====================================================================================
 *
 *       Filename:  vector.c
 *
 *    Description:  Funcoes para Vetores
 *
 *        Version:  1.0
 *        Created:  08/09/2016 08:11:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  pessoal
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector.h>


int *createVector(int size, int bound, int option){
	int i;
	int *vector = NULL;

	vector = (int*) malloc(sizeof(int)*size);

	switch(option){
		case RANDOM:
			srand(time(NULL));
			for(i = 0; i < size; i++)
				vector[i] = (rand()%bound);
			break;

		case INCREASE:
			for(i = 0; i < size; i++)
				vector[i] = i;
			break;

		case DECREASE:
			for(i = 0; i < size; i++)
				vector[i] = size-i;
			break;
	}
	return vector;

}

void printVector(int *vector, int size){
	int i;
	for(i = 0; i < size; i++)
		printf("%d\n", vector[i]);
}


