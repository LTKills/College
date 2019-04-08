/*
 * =====================================================================================
 *
 *       Filename:  utils.c
 *
 *    Description:  Useful tiny functions
 *
 *        Version:  1.0
 *        Created:  11/29/16 23:17:50
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


void swap(int *vec, int a, int b) {
	int aux = vec[a];
	vec[a] = vec[b];
	vec[b] = aux;
}


