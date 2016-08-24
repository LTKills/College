/*
 * =====================================================================================
 *
 *       Filename:  sorts.c
 *
 *    Description:  Algoritmos de Ordenacao
 *
 *        Version:  1.0
 *        Created:  08/09/2016 08:23:50 PM
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
#include <time.h>


void swap(int *a, int *b){
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void bubble(int *vector, int size){
	int i, j;
	for(i = 0; i < size; i++)
		for(j = 1; j < size-i; j++)
			if(vector[j] < vector[j-1])
				swap(&vector[j], &vector[j-1]);
}


void insertion(int *vector, int size){
	int i, j, key;
	for(i = 1; i < size; i++){
		j = i-1;
		key = vector[i];
		while(j >= 0 && key < vector[j]){
			vector[j+1] = vector[j];
			j--;
		}
		vector[j+1] = key;
	}
}



