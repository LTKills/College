#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
int n, q, r, i = 0;
int *result = NULL;
	scanf("%d", &n);
	//convertendo
	while(n >= 2){
   		q = n/2;
    	r = n%2;
    	n = q;
    	result = (int *) realloc(result, sizeof(int)*(i+1));
    	result[i++] = r;
	}
	result = (int *) realloc(result, sizeof(int)*(i+1));
	result[i] = n;

	//imprimindo
	n = 31;
	while(i < n){
		printf("0");
		n--;
	}
	while(i >= 0){
    	printf("%d",result[i--]);
	}
	printf("\n");
	free(result);
	return 0;
}
