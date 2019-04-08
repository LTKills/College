/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Maze runner
 *
 *        Version:  1.0
 *        Created:  11/02/16 14:04:55
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
#include <math.h>
#include <graph.h>

int main(int argc, char *argv[]) {
	int np, nc, ns;
	int i, j, pos, out, in;
	int start, solutions = 0;
	float **paths;
	struct VERTEX *vertex;

	// Read points
	scanf("%d", &np);
	vertex = malloc(sizeof(struct VERTEX) * np);

	for(i = 0; i < np; i++) {
		scanf("%f %f", &vertex[i].x, &vertex[i].y);
		vertex[i].out = 0; // no exit
		vertex[i].n = 0;
		vertex[i].links = NULL;
		vertex[i].valid = NULL;
		vertex[i].isCam = FALSE; //	not a chamber...yet
	}



	/* Chambers are only special if they have an exit,
	 * else it's just another point */

	// Read """"""chambers""""""" < no need for chambers lucas... tsc tsc
	scanf("%d", &nc);
	for(i = 0; i < nc; i++) {
		scanf("%d %d", &pos, &out);
		if(0 < pos && pos <= np) {		// checking
			vertex[pos-1].out = out;
			vertex[pos-1].isCam = TRUE;
		}
	}

	// Read segments
	scanf("%d", &ns);
	for(i = 0; i < ns; i++) {
		scanf("%d %d", &in, &out);

		// Checking portals
		if(0 < in && out > 0 && in != out && (abs(in) <= np) && (abs(out) <= np)){
		// build sparse matrix
			vertex[abs(in)-1].n++;
			vertex[abs(out)-1].n++;
			vertex[abs(in)-1].links = (int *) realloc(vertex[abs(in)-1].links, sizeof(int)*vertex[abs(in)-1].n);
			vertex[abs(in)-1].links[vertex[abs(in)-1].n-1] = out-1;
			vertex[abs(out)-1].links = (int *) realloc(vertex[abs(out)-1].links, sizeof(int)*vertex[abs(out)-1].n);
			vertex[abs(out)-1].links[vertex[abs(out)-1].n-1] = in-1;
		}
	}
	// Creating valid vectors
	for(i = 0; i < np; i++) vertex[i].valid = calloc(vertex[i].n, sizeof(int));

	scanf("%d", &start); // Cs
	if(start <= 0 || start > np) return -1; // checking consistency of start

	paths = exits(vertex, start-1, np, &solutions);

	paths = sortPaths(paths, solutions);

	printf("1 %d 0\n", start);
	for(i = 0; i < solutions; i++) {
		for(j = 0; j < (paths[i][0]+2); j++) {
			printf("%d ", (int)paths[i][j]);
		}
		printf("\n");
	}


	// Deallocating
	for(i = 0; i < np; i++) free(vertex[i].links);
	for(i = 0; i < np; i++) free(vertex[i].valid);
	free(vertex);
	for(i = 0; i < solutions; i++) free(paths[i]);
	free(paths);
	return 0;
}

