#ifndef _FILE_H_
#define _FILE_H_


#define ENTER 10
#define SPACE 32


typedef enum{
	INT,
	CHAR,
	UNSIGNED_CHAR,
	DOUBLE
} TYPE;



char *readLine(FILE* file, char delim);
void *readFile(FILE* file, TYPE opt, int *vecSize);

#endif
