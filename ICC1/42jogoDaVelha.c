/*
 * =====================================================================================
 *
 *       Filename:  42jogoDaVelha.c
 *
 *    Description:  Jogo da velha
 *
 *        Version:  1.0
 *        Created:  04/28/16 16:13:46
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

int main(int argc, char* argv[]){
	char tab[3][3];
	char check[3];
	int i, j, m, n, k;

	// transformando a porra toda em -1 (hehe)
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			tab[i][j] = -1;
		}
	}

	for(i = 0; i < 3; i++){	// invalidando todos os elementos de check
		check[i] = -1;
	}

	// recebendo jogadas... imprimindo resultados
	for(k = 0; k < 9; k++){
		scanf("%d %d", &m, &n);
		if(k % 2 == 0) tab[m][n] = 'X'; // X para o jogador 0
		else tab[m][n] = 'G';	// G para o jogador 1

		//	checando vencedores nas linhas
		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				check[j] = tab[i][j];
			}
			if(check[0] == 'X' && check[1] == 'X' && check[2] == 'X'){
				printf("0\n");
				return 0;
			}else if(check[0] == 'G' && check[1] == 'G' && check[2] == 'G'){
				printf("1\n");
				return 0;
			}
		}

		//	checando vencedores nas colunas
		for(j = 0; j < 3; j++){
			for(i = 0; i < 3; i++){
				check[i] = tab[i][j];
			}
			if(check[0] == 'X' && check[1] == 'X' && check[2] == 'X'){
				printf("0\n");
				return 0;
			}else if(check[0] == 'G' && check[1] == 'G' && check[2] == 'G'){
				printf("1\n");
				return 0;
			}
		}

		//	checando vencedores nas diagonais
		if(tab[0][0] == 'X' && tab[1][1] == 'X' && tab[2][2] == 'X'){
			printf("0\n");
			return 0;
		}else if(tab[2][0] == 'X' && tab[1][1] == 'X' && tab[0][2] == 'X'){
			printf("0\n");
			return 0;
		}

		if(tab[0][0] == 'G' && tab[1][1] == 'G' && tab[2][2] == 'G'){
			printf("1\n");
			return 0;
		}else if(tab[2][0] == 'G' && tab[1][1] == 'G' && tab[0][2] == 'G'){
			printf("1\n");
			return 0;
		}
	}
	printf("empate\n");
	return 0;
}
