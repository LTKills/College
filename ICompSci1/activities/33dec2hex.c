#include <stdio.h>
#include <stdlib.h>
int main(){
    long int n, q, r, i = 0;
    long int *result = NULL;
    scanf("%ld", &n);

    //convertendo
    while(n >= 16){
        q = n/16;
        r = n%16;
        n = q;
        result = (long int *) realloc(result, sizeof(long int)*(i+1));
        result[i++] = r;
    }
    result = (long int *) realloc(result, sizeof(long int)*(i+1));
    result[i] = n;

    //imprimindo
    while(i >= 0){
		if(result[i] == 10){
			printf("A");
			i--;
		}
		else if(result[i] == 11){
			printf("B");
			i--;
		}
		else if(result[i] == 12){
			printf("C");
			i--;
		}
		else if(result[i] == 13){
			printf("D");
			i--;
		}
		else if(result[i] == 14){
			printf("E");
			i--;
		}

		else if(result[i] == 15){
			printf("F");
			i--;
		}
		else
        	printf("%ld",result[i--]);
    }
    printf("\n");
    free(result);
    return 0;
}
