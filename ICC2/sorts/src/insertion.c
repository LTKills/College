/*
 * =====================================================================================
 *
 *       Filename:  insertion.c
 *
 *    Description:  Insertion Sort Implementation
 *
 *        Version:  1.0
 *        Created:  08/31/2016 12:53:52 AM
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



void insertionSort(int *vec, int size){
	int i, j, mine;

	for(i = 0; i < size; i++){
		j = i-1;
		while(j >= 0 && vec[j] > mine){
			vec[j+1] = vec[j];
			j--;
		}
		vec[j+1] = mine;
	}
}
