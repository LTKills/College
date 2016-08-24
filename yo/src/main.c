#include <stdlib.h>
#include <stdio.h>
#include <vector.h>
#include <sorts.h>



int main(int argc, char *argv[]){
	int *vector;

	vector = createVector(50, 50, RANDOM);
	bubble(vector, 50);

	return 0;
}

