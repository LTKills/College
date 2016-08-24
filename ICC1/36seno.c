#include <stdio.h>
#include <math.h>


double fatorial(int i){		//calcula fatorial :D
	int j;
	double fat = 1;
	
	for(j = 1; j <= i; j++){
		fat *= j;
	}
	return fat;
}


double seno(double x){
	int i, j;
	double loppa = x;
	for(i = 2; i <=  301; i++){ 			// calculando a série de Taylor
	j = (i*2) - 1;
		if(i % 2 == 0){
			loppa -= (pow(x, j)) / fatorial(j);	// positivo caso i par
		}else{
			loppa += (pow(x, j)) / fatorial(j);	// negativo caso i impar
		}	
	}
	return loppa;
}


int main(int argc, char *argv[]){
	double x;
	
	scanf("%lf", &x);
	
	printf("%lf\n", seno(x));
	
	return 0;
}
