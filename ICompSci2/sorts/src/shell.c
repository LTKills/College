/*
 * =====================================================================================
 *
 *       Filename:  shell.c
 *
 *    Description:  Shell sort implementation
 *
 *        Version:  1.0
 *        Created:  11/28/16 17:11:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  The University of Sao Pulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>



void shellSort(int *vec, int size) {
	int i, j, h, key;

	for(h = 1; h < size/3; h = 3*h + 1); // initialize with high h

	while(h >= 1) { 		// decrease h till its 1
		for(i = h; i < size; i++) {
			key = vec[i];
			j = i - h;
			while(j >= 0 && key < vec[j]) {
				vec[j + h] = vec[j];
				j -= h;
			}
			vec[j + h] = key;
		}
		h /= 3;
	}
}

