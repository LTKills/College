
// ---------> LTKills

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int isPrime(int n){
	int i;
	for(i = 2; i < n; i++)
		if(n%i == 0) return 0;
	return 1;
}

int main(void){
	int i, j = 1, n, c = 0;
	double sum = 0;
	scanf("%d", &n);
	int prime[n];

	for(i = 2; i <= n; i++){
		if(i >= (c+2)) prime[c++] = isPrime(i);
		if(prime[i-2] && j%2 != 0){
			sum += (1/(double)i);
			j++;
		}else if(prime[i-2]){
			sum -= (1/(double)i);
			j++;
		}
	}
		printf("%lf\n", sum);
	return 0;
}
