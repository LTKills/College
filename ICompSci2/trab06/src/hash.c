/*
 * =====================================================================================
 *
 *       Filename:  hash.c
 *
 *    Description:  Hashing functions implementation
 *
 *        Version:  1.0
 *        Created:  11/14/16 14:10:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization: 	The University of Sao Pulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <file.h>
#include <hash.h>

// Swap elements of vector
void swapPos(int *positions, int a, int b) {
	int aux = positions[a];
	positions[a] = positions[b];
	positions[b] = aux;
}

// Swap words
void swap(char **vec, int a, int b) {
	char *aux = vec[a];
	vec[a] = vec[b];
	vec[b] = aux;
}

// Sort words
void bubbleSort(char **vec, int n) {
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 1; j < n-i; j++)
			if(strcmp(vec[j], vec[j-1]) < 0) swap(vec, j, j-1);
}

int calcMax(struct ANAGRAM *anagram, int n) {
	int i, j, max = 0;
	for(i = 0; i < n; i++) {
		if(anagram[i].n == 0) continue;
		if(anagram[i].n > max) max = anagram[i].n; // update max anagram value
		bubbleSort(anagram[i].q, anagram[i].n);				// sorting anagrams' vector
	}
	return max;
}

// Test if is colision
int test(char *string1, char *string2) {
	int i, op, n1 = strlen(string1), n2 = strlen(string2);
	int *a = calloc(28, sizeof(int)), *b = calloc(28, sizeof(int));
	char aux;

	if(n1 != n2) {
		free(a);
		free(b);
		return FALSE;
	}

	for(i = 0; i < n1; i++) {
		aux = toupper(string1[i]);
		if(aux == ' ') a[26]++;
		else if(aux == '-') a[27]++;
		else a[aux - 'A']++;
	}

	for(i = 0; i < n1; i++) {
		aux = toupper(string2[i]);
		if(aux == ' ') b[26]++;
		else if(aux == '-') b[27]++;
		else b[aux - 'A']++;
	}

	for(i = 0; i < 28; i++)
		if(a[i] != b[i]) op = FALSE;

	op = TRUE;

	free(a);
	free(b);

	return op;
}

// Returns a prime number
int prime(char a) {
	a = toupper(a);
	if(a == 'A') return 2;
	else if(a == 'B') return 3;
	else if(a == 'C') return 5;
	else if(a == 'D') return 7;
	else if(a == 'E') return 11;
	else if(a == 'F') return 13;
	else if(a == 'G') return 17;
	else if(a == 'H') return 19;
	else if(a == 'I') return 23;
	else if(a == 'J') return 29;
	else if(a == 'K') return 31;
	else if(a == 'L') return 37;
	else if(a == 'M') return 41;
	else if(a == 'N') return 43;
	else if(a == 'O') return 47;
	else if(a == 'P') return 53;
	else if(a == 'Q') return 59;
	else if(a == 'R') return 61;
	else if(a == 'S') return 67;
	else if(a == 'T') return 71;
	else if(a == 'U') return 73;
	else if(a == 'V') return 79;
	else if(a == 'W') return 83;
	else if(a == 'X') return 89;
	else if(a == 'Y') return 97;
	else if(a == 'Z') return 101;
	else if(a == '-') return 103;
}

// Calculate code for given string
int hash(char *string, int n) {
	long long unsigned int pos = 1;
	int i;

	for(i = 0; i < strlen(string); i++) {
		pos *= prime(string[i]);
	}

	pos = pos % SIZE;
	return pos;
}


