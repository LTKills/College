/*
 * =====================================================================================
 *
 *       Filename:  56tesouro.c
 *
 *    Description:  Tesouro Direto
 *
 *        Version:  1.0
 *        Created:  05/22/16 17:12:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  USP
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


long double calc(long double **tab, int row, int meses){
	long double k = 0;
	long double rent = 0, juros = 0;
	k = ((tab[row][0]*tab[row][1]))*pow(1+tab[row][2],meses-row);
	rent = k - (tab[row][0]*tab[row][1]);			//	rentabilidade bruta
	if(meses-row <= 5)
		juros = rent*(0.225);

	else if(meses-row <= 11)
		juros = rent*(0.2);

	else if(meses-row <= 23)
		juros = rent*(0.175);

	else
		juros = rent*(0.15);

	return k - juros;
}

int main(void){
	int meses = 0, i, j;
	long double k = 0;
	long double **tab;

	tab = (long double**) malloc(sizeof(long double*)*500);
	for(i = 0; i < 500; i++)
		tab[i] = calloc(3,sizeof(long double));


	while(tab[meses][0] != -1){
		scanf("%Lf", &tab[meses][0]);
		if(tab[meses][0] == 0){
			meses++;
			continue;
		}if(tab[meses][0] == -1) break;

		scanf("%Lf %Lf", &tab[meses][1], &tab[meses][2]);
		meses++;
	}
	for(i = 0; i < meses; i++){
		if(tab[i][0] != 0)
			k += calc(tab, i, meses);
	}
	printf("%.2Lf\n", k);

	for(i = 0; i < 500; i++) free(tab[i]);
	free(tab);
	return 0;
}

