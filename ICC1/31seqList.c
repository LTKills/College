#include <stdlib.h>
#include <stdio.h>


float *sortVector(float*numbers, int n){
    int i, j;
    float aux = 0;

    for(i = 1; i < n; i++){
        for(j = 0; j < i; j++){
            if(numbers[i] < numbers[j]){
                aux = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = aux;
            }
        }
    }
    return numbers;
}


int main(int argc, char *argv[]){
    int n, i, j;
    float *numbers = NULL;
    int *p = NULL;

    scanf("%d", &n);
    numbers = malloc(sizeof(int)*n);
    p = calloc(n, sizeof(int));

    for(i = 0; i < n; i++){
        scanf("%f", &numbers[i]);
    }

    numbers = sortVector(numbers, n); // ordenando

    j = 0;
    for(i = 0; i < n; i++){
		if(i == 0){
			p[j]++;
		}
        else if(numbers[i] == numbers[i-1])
            p[j]++;
        else
            p[++j]++;
    }
    j = -1;
    i = 0;
    printf("%.1f %d\n", numbers[i], p[++j]);
    i = p[j];
    for(; i < n && p[j] != 0; i += p[j]){
        printf("%.1f %d\n", numbers[i], p[++j]);
    }



    return 0;
}
