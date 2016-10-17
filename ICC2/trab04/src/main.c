/*
 * =====================================================================================
 *
 *       Filename:  learning.c
 *
 *    Description:  Machine Learning using K-nearest neightbours
 *
 *        Version:  1.0
 *        Created:  10/07/2016 02:25:51 PM
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
#include <file.h>


int main(int argc, char *argv[]){
	char *train, *class, *test;
	int i, nMasks = 0, *dimensions;

	/*Reading inputs*/
	train = readLine(stdin);
	class = readLine(stdin);
	test = readLine(stdin);
	scanf("%d", &nMasks);

	dimensions = malloc(sizeof(int)*nMasks);
	for(i = 0; i < nMasks; i++)
		scanf("%d", *dimensions[i]);
	/*Inputs read*/

	free(dimensions);
	free(train);
	free(class);
	free(test);

	return 0;
}

