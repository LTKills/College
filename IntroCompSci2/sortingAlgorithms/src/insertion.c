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


void insertionSort(int *vec, int size) {
	int i, j, key;

	for(i = 1; i < size; i++) {
		key = vec[i];
		j = i-1;

		while(j >= 0 && vec[j] > key) {
			vec[j+1] = vec[j];
			j--;
		}
		vec[j+1] = key;
	}
}
