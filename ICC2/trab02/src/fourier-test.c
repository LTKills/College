/*Code by LTKills*/

#include <stdlib.h>
#include <stdio.h>
#include <file.h>
#include <complex.h>
#include <math.h>

#define SIZE UNSIGNED_CHAR

/*Standard swapping algorithm*/
void swap(double *vec, int a, int b){
	double aux;

	aux = vec[a];
	vec[a] = vec[b];
	vec[b] = aux;

}


/*Whooooooooooooa Fourier! -> Discrete Fourier Transform*/
double complex *dft(unsigned char *raw, int N){
	int k, t;
	double complex *inducts = malloc(sizeof(double complex)*N/2);
	double x;
	double complex z;

	for(k = 0; k < N/2; k++){
		z = 0;
		for(t = 0; t < N; t++){ // Calculate intern product betwen sinusoid of frequecy k and given function
			x = k * 2 * M_PI * t / N; // Generate angle (or exponent, in case of e^x)
			z += (cos(x) - I*sin(x))*raw[t];
		}

		if(k == 0)
			inducts[k] = (1.0/N)*z;
		else
			inducts[k] = (2.0/N)*z;
	}
	return inducts;

}

/*Organize coefficients (inducts) by descending magnitude order and store original places*/
double *magsDecrease(double complex *inducts, int N, int *places){
	int i, j, aux;
	double *mags = malloc(sizeof(double)*N);

	for(i = 0; i < N; i++)
		mags[i] = cabs(inducts[i]);

	for(i = 0; i < N; i++){ 			// Bubble sort swapping both magnitudes and places
		for(j = 1; j < N-i; j++){
			if(mags[j] > mags[j-1]){
				swap(mags, j, j-1);
				aux = places[j-1];
				places[j-1] = places[j];
				places[j] = aux;
			}
		}
	}

	return mags;
}

/*Zero the N-C least significant coefficients*/
void magsZeroing(double *mags, int N, int *places, int bound, double complex *inducts){

	while(bound < N){
		inducts[places[bound]] = 0;
		bound++;
	}

}

/*Inverse Discrete Fourier Transform -> Generate clean signal*/
unsigned char *inverseDft(double complex *inducts, int N){
	unsigned char *ans = malloc(sizeof(unsigned char) * N);
	int k, t;
	double x;
	double complex z;

	for(k = 0; k < N; k++){
		z = 0;

		for(t = 0; t < N/2; t++){ // Calculate intern product betwen sinusoid of frequecy k and given function
			x = k * 2 * M_PI * t / N; // Generate angle (or exponent, in case of e^x)
			z += (cos(x) + I*sin(x))*inducts[t];
		}


		ans[k] = (unsigned char) round(creal(z)); // Round b4 casting cuz casting makes (for example) 124.9 = 124
												  // We need 124.9 = 125 ;)
	}

	return ans;
}



int main(int argc, char *argv[]){
	char *file;
	unsigned char *raw;
	int c, size = 0, i;
	double complex *inducts;
	double *mags;
	int *places;
	FILE *fp;

/*	Reading from file and C (lower bound).Input is like:

	 	"file"
	 	"C"

*/
	file = readLine(stdin);
	fp = fopen(file, "rb");
	free(file);
	scanf("%d", &c);

	raw = (unsigned char*) readFile(fp, SIZE, &size);

	fclose(fp);
	/*=====================================*/

	inducts = dft(raw, size);


	/*Organizing magnitudes for zeroing*/
	places = malloc(sizeof(int)*size/2);
	for(i = 0; i < size/2; i++) places[i] = i;
	mags = magsDecrease(inducts, size/2, places);
	/*=================================*/


	magsZeroing(mags, size/2, places, c, inducts); // Zeroing organized magnitudes

	/*Freeing*/
	free(mags);
	free(places);
	/*=======*/


	free(raw); // <- Special Free :)


	raw = inverseDft(inducts, size); // Raw is being malloc'd again


	free(raw); // freeing raw again :D
	free(inducts);
	return 0;

}
