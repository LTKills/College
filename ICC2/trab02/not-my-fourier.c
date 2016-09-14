#include <fourier.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Função que calcula a amplitude de um número complexo z*/
double amplitude(complex double z) {
	return sqrt(creal(z)*creal(z) + cimag(z) * cimag(z));
}

/* Função que realiza a transformada discreta de Fourier como descrita na equação (10) da descrição do trabalho */
complex double * fourier_coefficients(byte * observations, int n) {
	int k, j;
	complex double ck; //variável de acumulação
	complex double a = (acos(-1) * (-2.0) * I)/n; //a: constante
	complex double * coefficients = (complex double *) malloc(sizeof(complex double) * (1+n/2)); //vetor de coeficientes

	for(k = 0; k <= n/2; ++k) {
        ck = 0.0;
		for(j = 0; j < n; ++j) {
			ck += observations[j] * cexp(a * k * j);
		}
        if(!k) ck /= n;
        else ck *= (2.0)/n;
		coefficients[k] = ck;
	}

	return coefficients;
}

/* Função que retorna o vetor de amplitudes dos coeficientes */
double * fourier_amplitudes(complex double * coefficients, int n) {
	int j;
	double * amplitudes = (double *) malloc(sizeof(double) * (1+n));
	int nAmplitudesRelevantes = 0;

	for(j = 0; j <= n; ++j) { 
		amplitudes[j] = amplitude(coefficients[j]);
		if(amplitudes[j] > 0.1) ++nAmplitudesRelevantes;
	}

	printf("%d\n", nAmplitudesRelevantes); //segunda saída: número de amplitudes relevantes (maiores do que 0.1)

	return amplitudes;
}

/* Função que filtra os coeficientes, isto é: ordena o vetor de coeficientes a partir de suas amplitudes e, dada a entrada C, zera
todos os coeficientes do vetor excetor os C primeiros */
void fourier_filterCoefficients(double *amplitudes, complex double * coefficients, int c, int n) {
	int * indexes;
	int j;
	indexes = mergeSort(amplitudes, n+1);

	for(j = c; j <= n; ++j) {
		coefficients[indexes[j]] = 0.0;
		amplitudes[indexes[j]] = 0.0;
	}

	//terceira saída do trabalho: sequência dos C maiores coeficientes convertidas para inteiro
	for(j = 0; j < c; ++j) printf("%d ", (int) amplitudes[indexes[j]]); 
    printf("\n");
	free(indexes);
}

/* Realiza a transformada inversa de Fourier e retorna o resultado no vetor */
byte * fourier_inverseTransform(complex double * coefficients, int n) {
	int j, k;
	complex double xj; 
    complex double a = (acos(-1) * (2.0) * I)/n; //a: constante como a de fourier_coefficients
	byte * result = (byte *) malloc(sizeof(byte) * n);

	for(j = 0; j < n; ++j) {
		xj = 0.0;
		for(k = 0; k <= n/2; ++k) {
			xj += coefficients[k] * cexp(a * k * j);
		}
		result[j] = (byte) round(creal(xj)); 
	}
	return result;
}
