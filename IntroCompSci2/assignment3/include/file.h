#ifndef _FILE_H_
#define _FILE_H_

typedef enum{
	INT,
	CHAR,
	UNSIGNED_CHAR,
	DOUBLE
} TYPE;

char *readLine(FILE* file);
void *readFile(FILE* file, TYPE opt, int *vecSize);

#endif
