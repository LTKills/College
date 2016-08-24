#ifndef _VECTOR_H_
#define _VECTOR_H_

enum{
	RANDOM, // 0
	INCREASE, // 1
	DECREASE // 2
};


int *createVector(int size, int bound, int option);
void printVector(int *vector, int size);

#endif

