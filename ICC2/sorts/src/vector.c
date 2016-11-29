/*
 * =====================================================================================
 *
 *       Filename:  vector.c
 *
 *    Description:  Vector manipulation functions
 *
 *        Version:  1.0
 *        Created:  11/26/16 10:39:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: 	LTKills
 *   Organization:  The University of Sao Paulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


/*Prints vector*/
void printVec(int *vec, int size) {
	int i;
	for(i = 0; i < size; i++) printf("%d\n", vec[i]);
}


/*Generates random vector of 'size' elements no greater than 'bound'*/
int *randVec(int bound, int size) {
	int i;
	int *vec = malloc(sizeof(int) * size);
	srand(time(NULL));

	for(i = 0; i < size; i++)
		vec[i] = rand()%bound;

	return vec;
}

