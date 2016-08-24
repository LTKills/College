#include <stdlib.h>
#include <stdio.h>

// n: tamanho do vetor
//
// PIOR CASO DE EXECUÇÃO
// =====================
// f(n) = c0 + c1 + c2 * n + c3
// a = c2
// b = c0 + c1 + c3
// f(n) = a*n + b (linear)
//
// MELHOR CASO DE EXECUCAO
// =======================
// g(n) = c0 + c1 + c2 + c3
// a' = c0 + c1 + c2 + c3
// g(n) = a' (custo contante)
//
// CASO MÉDIO DE EXECUÇÃO
// ======================
// h(n) = c0 + c1 + 1/2 * c2 * n + c3
// a'' = 1/2 * c2
// b'' = c0 + c1 + c3
// h(n) = a'' * n + b'' (linear)
//
int sequential_search(int *vector, int n, int key) {	// c0
	int i;						// c1
	for (i = 0; i < n; i++) {			// n
		if (vector[i] == key) {			// c2
			return i;			// c3
		}
	}
	return -1;					// c3
}

//
// EQUAÇÃO DE RECORRÊNCIA
// ======================
//
// PIOR CASO
// =========
// F(n) = c0 + c1 + c2 + c3 + c4 + c6 + c7 + F(n/2)
// F(n/2) = c0 + c1 + c2 + c3 + c4 + c6 + c7 + F(n/2/2)
// F(n/2/2) = c0 + c1 + c2 + c3 + c4 + c6 + c7 + F(n/2/2/2)
// ...
// a = c0 + c1 + c2 + c3 + c4 + c6 + c7
//
// F(n) = F(n/2) + a
// F(n) = a + a log_2(n)   (custo logarítmico)
//
// MELHOR CASO
// ===========
//
// G(n) = c0 + c1 + c2 + c3 + c4 + c5
// a' = c0 + c1 + c2 + c3 + c4 + c5
// G(n) = a' (custo é constante)
//
// CASO MÉDIO
// ==========
//
// F(n) = F(n/2) + a
// F(n) = a/2 + a/2 log_2(n)   (custo logarítmico)
//
int binary_search(int *vector, int start, int end, int key) {		// c0
	int middle;							// c1
	if (start > end) return -1;					// c2
	middle = (start+end)/2;						// c3
	if (vector[middle] == key) {					// c4
		return middle;						// c5
	} else if (key > vector[middle]) {				// c6
		return binary_search(vector, middle+1, end, key);	// rec
	} else if (key < vector[middle]) {				// c7=c6
		return binary_search(vector, start, middle-1, key);	// rec
	}
}






