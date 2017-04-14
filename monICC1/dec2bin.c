#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int a, vec[10], i;

    printf("Hit me babay one more time: ");
    scanf("%d", &a);

    for(i = 0; a >= 1; i++) {
        vec[i] = a%2;
        a /= 2;
    }

    i--;
    while(i >= 0) {
        printf("%d", vec[i]);
        i--;
    }
    printf("\n");

    return 0;
}
