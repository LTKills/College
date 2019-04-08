#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <graph.h>
#include <stack.h>

float euclidean_distance(struct VERTEX vec1, struct VERTEX vec2) {
	float dist;
	dist = sqrt(pow(vec1.x-vec2.x,2) + pow(vec1.y-vec2.y,2));
	return dist;
}

int isExit(struct VERTEX vertex) {
	if(vertex.out != FALSE) return TRUE;
	return FALSE;
}

void swap(float **paths, int i, int j) {
	float *aux = paths[i];
	paths[i] = paths[j];
	paths[j] = aux;
}

void untie(float **paths, int a, int b) {
	int i;

	for(i = 1; i < paths[a][0]+2; i++) {
		if(paths[a][i] < paths[b][i]) return;
		if(paths[a][i] > paths[b][i]) {
			swap(paths, a, b);
			return;
		}
	}
}

float **sortPaths(float **paths, int solutions) {
	int i, j, first;

	// Bubble :D
	for(i = 0; i < solutions; i++)
		for(j = 0; j < (solutions)-1; j++) {
			if(paths[j][(int)paths[j][0]+1] > paths[j+1][(int)paths[j+1][0]+1]) swap(paths, j, j+1);
		}


	for(i = 0; i < solutions; i++)
		for(j = 0; j < (solutions)-1; j++) {
			if(paths[j][(int)paths[j][0]+1] == paths[j+1][(int)paths[j+1][0]+1]) untie(paths, j, j+1);
		}

	return paths;
}


// Adding one answer to the paths (answers) matrix
float **buildAns(float **paths, struct STACK *stack, struct VERTEX *vertex, int *solutions) {
	int i;
	float dist = 0;

	(*solutions)++;
	paths = realloc(paths, sizeof(float *) * (*solutions));
	paths[(*solutions)-1] = malloc(sizeof(float) * (stack->used+2));

	paths[(*solutions)-1][0] = stack->used;
	for(i = 1; i <= stack->used; i++) {
		paths[(*solutions)-1][i] = stack->q[i-1]+1;
		if(i < stack->used)
			dist += euclidean_distance(vertex[stack->q[i]], vertex[stack->q[i-1]]);
	}
	paths[(*solutions)-1][i] = dist;

	if(dist == 0) {
		free(paths[(*solutions)-1]);
		(*solutions)--;
		paths = realloc(paths, sizeof(float *) * (*solutions));
	}

	return paths;
}

float **exits(struct VERTEX *vertex, int start, int np, int *solutions) {
	struct STACK *stack = createStack(np);
	float **paths = NULL;
	int i, j, k, cur, next;

	push(stack, start);

	while(emptyStack(stack) == FALSE) { // while not empty
		cur = pop(stack);

		for(i = 0; i < vertex[cur].n; i++) {
			if(vertex[cur].valid[i] >= 0) { // if can go, go
				next = vertex[cur].links[i];

				// Check if it is on stack
				for(k = 0; k < stack->used && next != stack->q[k]; k++);
				if(k == stack->used) {	// If it's not, push
					push(stack, next);

					// Invalidate cur in next
					for(j = 0; vertex[next].links[j] != cur; j++);
					vertex[next].valid[j] = -1;

				}

				// Invalidate next in cur
				vertex[cur].valid[i] = -1;

				break;
			}
		}
		//Resetting current vertix for future paths
		if(i == vertex[cur].n) { // No valid paths
			for(i = 0; i < vertex[cur].n; i++)
				vertex[cur].valid[i] = 0; // Validating all neighbours
			if(isExit(vertex[cur]))
				paths = buildAns(paths, stack, vertex, solutions);
			rmLast(stack);
		}
	}

	deleteStack(stack);
	return paths;
}

