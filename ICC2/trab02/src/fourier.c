/*Code by LTKills*/

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


/*Whooooooooooooa Fourier!*/
double complex *inductGen(unsigned char *raw, int N){
	int k, t, n;
	double complex *inducts = malloc(sizeof(double complex)*N/2);
	double x, pi = M_PI;
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
	double *mags = malloc(sizeof(double complex)*N);

	for(i = 0; i < N; i++)
		mags[i] = cabs(inducts[i]);

	for(i = 0; i < N; i++){
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
	int i;

	for(i = 0; i < bound; i++);
	while(i < N){
		inducts[places[i]] = 0;
		i++;
	}
}

/*Inverse Fourier Transform -> Generate clean signal*/
unsigned char *inverseGen(double complex *inducts, int N){
	unsigned char *ans = malloc(sizeof(unsigned char) * N);
	int k, t, i;
	double x;
	double complex z;

	for(k = 0; k < N/2; k++){
		z = 0;

		for(t = 0; t < N; t++){ // Calculate intern product betwen sinusoid of frequecy k and given function
			x = k * 2 * M_PI * t / N; // Generate angle (or exponent, in case of e^x)
			z += (cos(x) - I*sin(x))*inducts[k];
		}

		ans[k] = (unsigned char) z;
	}
	i = k;
	for(; k >= 0; k--){
		z = 0;
		for(t = 0; t < N; t++){
			x = k * 2 * M_PI * t / N;
			z += (cos(x) - I*sin(x))*inducts[k];
		}

		ans[i++] = (unsigned char) creal(z);
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

	inducts = inductGen(raw, size);
	free(raw);

	places = malloc(sizeof(int)*size/2);
	for(i = 0; i < size/2; i++) places[i] = i;
	mags = magsDecrease(inducts, size/2, places);

	/*STDOUT lines*/
	printf("%d\n", size);
	for(i = 0; mags[i] > 0.1; i++);
	printf("%d\n", i);

	for(i = 0; i < c-1; i++) printf("%d ", (int) mags[i]);
	printf("%d\n", (int) mags[i]);
	/*======================*/


	printf("\n\nC=%d\n\n", c);
	magsZeroing(mags, size/2, places, c, inducts);
	/*Testing*/
	//for(i = 0; i < size/2; i++)
	//	printf("R=%lf\tIm=%lf\n", creal(inducts[i]), cimag(inducts[i]));
	/*=======*/
	free(mags);
	free(places);


	raw = inverseGen(inducts, size);

	fp = fopen("my-beautiful-new-audio.raw", "w+");

	for(i = 0; i < size; i++)
		fwrite(raw, sizeof(unsigned char), size, fp);

	fclose(fp);
	free(raw);
	free(inducts);
	return 0;

}
