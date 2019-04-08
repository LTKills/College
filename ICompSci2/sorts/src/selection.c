/*
 * =====================================================================================
 *
 *       Filename:  selection.c
 *
 *    Description:  Selection Sort Implementation
 *
 *        Version:  1.0
 *        Created:  11/25/16 21:30:37
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
#include <limits.h>


void selectionSort(int *vec, int size) {
	int i, j, pos, min;

	for(i = 0; i < size; i++) {
		min = INT_MAX;
		for(j = i; j < size; j++) {
			if(vec[j] < min) {
				pos = j; 		// Saves the position
				min = vec[j];
			}
		}
		vec[pos] = vec[i]; // Saving the element before it is overriden
		vec[i] = min;
	}
}
