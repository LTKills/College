#ifndef _GRAPH_H_
#define _GRAPH_H_

struct VERTEX {
	float x, y, dist;
	int out;
	int isCam;
	int n;
	int *links; // paths
	int *valid; // valid paths
};

enum {
	FALSE,
	TRUE
};

float **exits(struct VERTEX *vertex, int start, int np, int *sol);
float **sortPaths(float **paths, int solutions);

#endif

