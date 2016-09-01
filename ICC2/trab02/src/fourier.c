#include <stdlib.h>
#include <stdio.h>
#include <file.h>
#include <complex.h>
#include <math.h>

#define SIZE UNSIGNED_CHAR


void swap(double *vec, int a, int b){
	double aux;

	aux = vec[a];
	vec[a] = vec[b];
	vec[b] = aux;

}


double complex *inductGen(unsigned char *raw, int N){
	int k, t, n;
	double complex *inducts = malloc(sizeof(double complex)*N);
	double x, pi = M_PI;
	double complex z;

	for(k = 0; k < N; k++){

		z = 0;

		for(t = 0; t < N/2; t++){
			x = k * 2 * M_PI * t / N;
			z += sin(x) + I*cos(x);
		}

		if(k == 0)
			inducts[k] = (1.0/N)*raw[k]/z;
		else
			inducts[k] = (2.0/N)*raw[k]/z;

	}
	return inducts;

}

double *magsDecrease(double complex *inducts, int N, int *places){
	int i, j;
	double *mags = malloc(sizeof(double complex)*N);

	for(i = 0; i < N; i++)
		mags[i] = cabs(inducts[i]);

	for(i = 0; i < N; i++){
		for(j = 1; j < N-i; j++){
			if(mags[j] > mags[j-1]){
				swap(mags, j, j-1);
				places[j] = j-1;
				places[j-1] = j;
			}
		}
	}

	return mags;
}


void magsZeroing(double *mags, int N, int *places, int bound, double complex *inducts){
	int i;

	for(i = 0; mags[i] >= bound; i++);
	while(i < N){
		inducts[places[i]] = 0;
		i++;
	}


}

unsigned char *inverseGen(double complex *inducts, int N){
	unsigned char *ans = malloc(sizeof(unsigned char) * N);
	int k, t, i;
	double x;
	double complex z;

	for(k = 0; k < N; k++){

		z = 0;

		for(t = 0; t < N/2; t++){
			x = k * 2 * M_PI * t / N;
			z += sin(x) + I*cos(x);
		}
		ans[k] = (unsigned char) inducts[k]*z;
	}

	return ans;
}


int main(int argc, char *argv[]){
	char *file;
	unsigned char *raw;
	int c, size, i;
	double complex *inducts;
	double *mags;
	int *places;
	FILE *fp;

	file = readLine(stdin);
	fp = fopen(file, "rb");
	free(file);
	scanf("%d", &c);

	raw = (unsigned char*) readFile(fp, SIZE, &size);
	fclose(fp);

	places = malloc(sizeof(int)*size);
	inducts = inductGen(raw, size);
	free(raw);

	mags = magsDecrease(inducts, size, places);

	magsZeroing(mags, size, places, c, inducts);
	free(mags);
	free(places);


	raw = inverseGen(inducts, size);

	/*Testing*/
	for(i = 0; i < size; i++)
		printf("R=%d\n", raw[i]);


	free(inducts);
	return 0;

}
