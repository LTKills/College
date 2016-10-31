#ifndef _FILE_H_
#define _FILE_H_

typedef enum{
	INT,
	CHAR,
	UNSIGNED_CHAR,
	DOUBLE
} TYPE;

double euclidean_distance(double *vec1, double *vec2, int len);
char *readLine(FILE* file);
void *readFile(FILE* file, TYPE opt, int *vecSize);

#endif
