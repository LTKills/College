#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double media(int n, double m, double past){
    double media;
    media = past + (m-past)/(n+1);
    return media;
}

double vare(int n, double pastVar, double currVec, double pastAv){
    double var;
    var = (((n-1)*pastVar)/n) + pow((currVec - pastAv),2)/(n+1);
    return var;
}

int main(void){
    int i = 0, n;
    double vec[500];
    double av[500];
    double var[500];

    while(scanf("%lf", &vec[i++]) != EOF);
    i--;

    av[1] = (vec[0] + vec[1])/2;
    for(n = 2; n < i; n++)
        av[n] = media(n, vec[n], av[n-1]);

    var[1] = pow((vec[0] - av[1]),2) + pow((vec[1] - av[1]),2);
    for(n = 2; n < i; n++)
        var[n] = vare(n, var[n-1], vec[n], av[n-1]);

	printf("%.2lf", av[1]);
    for(n = 2; n < i; n++)
        printf(" %.2lf", av[n]);
    printf("\n");

	printf("%.2lf", var[1]);
    for(n = 2; n < i; n++)
        printf(" %.2lf", var[n]);
    printf("\n");


    return 0;
}
