#ifndef _BIN3_H_
#define _BIN3_H_

typedef NODE NODE;

typedef struct{
	int val;
	NODE  *left, *right, *up;
} node;


insertBin3();
searchBin3();
removeBin3();
printBin3();


#endif
