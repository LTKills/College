#include <stdlib.h>
#include <stdio.h>

// PIOR CASO 
// =========
//
// i) Certeza de que key < vector[i] para todos os casos do laço interno
//
// Força Bruta
// ===========
// F1(i) = (i+1)*(c4 + c5)
// a = c4 + c5
// F1(i) = (i+1)*a = a*i + a
//
// Eq Recorrência
// ==============
// F1(i) = F(i-1) + c4 + c5
// F1(i) = F(i-1) + a, i >= 0
// 	 = a*i + a
//
// Eq. Recorrência
// ===============
// F2(j,n) = c2 + c3 + F1(j-1) + c6 + F2(j+1, n), j < n
// a' = c2 + c3 + c6
//
// F2(j,n) = F1(j-1) + a' + F2(j+1, n), j < n
// F2(j,n) = (a*i+a) + a' + F2(j+1, n), j < n
// 	i = j-1
// F2(j,n) = (a*(j-1)+a) + a' + F2(j+1, n), j=1, j < n
// F2(j,n) = a*j +a' + F2(j+1, n)
// F2(j,n) = a/2*n^2 + (a' - a/2)*n - a' (quadrática em termos do tam n vetor)
//
// MELHOR CASO 
// ===========
//
// i) Certeza de que key >= vector[i] para todos os casos do laço interno
//
// F1(i) = a*i + a
// 	--> nunca o laço mais interno será executado...
//
// F2(j,n) = c2 + c3 + F1(j-1) + c6 + F2(j+1, n), j < n
// F2(j,n) = c2 + c3 + 0 + c6 + F2(j+1, n), j < n
// F2(j,n) = + F2(j+1, n), j < n
// a'' = c2 + c3 + 0 + c6 
// F2(j,n) = a'' + F2(j+1, n), j < n
// F2(j,n) = (n-1) * a'' = a''*n - a'' (linear em termos de n)
//
void insertion(int *vector, int n) {			// c0
	int i, j, key;					// c1

	// F2
	for (j = 1; j < n; j++) {			// n-1
		key = vector[j];			// c2
		i = j-1;				// c3

		// F1
		while (i >= 0 && key < vector[i]) {	// i+1
			vector[i+1] = vector[i];	// c4
			i--;				// c5
		}
		vector[i+1] = key;			// c6
	}
}






