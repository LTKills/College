/*
 * =====================================================================================
 *
 *       Filename:  bubble.c
 *
 *    Description:  Bubble Sort Implementation
 *
 *        Version:  1.0
 *        Created:  08/31/2016 12:50:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  NONE
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>


void swap(int *vec, int a, int b){
	int aux;

	aux = vec[a];
	vec[a] = vec[b];
	vec[b] = aux;

}


void bubbleSort(int *vec, int size){
	int i, j;
	for(i = 0; i < size; i++)
		for(j = 1; j < size-i; j++)
			if(vec[j] < vec[j-1]) swap(vec, j, j-1);
}


