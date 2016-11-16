/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Anagrams
 *
 *        Version:  1.0
 *        Created:  11/08/16 17:09:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  The University of Sao Paulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <file.h>
#include <hash.h>


int main(int argc, char *argv[]) {
	int i, j, k, max, code, pos = 0, most = 0;
	FILE *fp;
	char *string, *filename = readLine(stdin);
	struct ANAGRAM *anagrams;
	int *positions = NULL;

	fp = fopen(filename, "r");

	anagrams = calloc(SIZE, sizeof(struct ANAGRAM));

	// Reading names and hashing
	while(!feof(fp)) {
		string = readLine(fp);
		if(feof(fp)) break;

		// Create unique code for each anagram
		code = hash(string, strlen(string));
		pos = code;

		// Check if it is a colision
		for(k = 1; anagrams[pos].n > 0 && test(string, anagrams[pos].q[0]) == FALSE; k++) pos = code + (k*k); // Quadratic probing

		// Insert on hash table
		anagrams[pos].n++;
		anagrams[pos].q = realloc(anagrams[pos].q, sizeof(char *) * anagrams[pos].n);
		anagrams[pos].q[anagrams[pos].n-1] = string;
	}

	// Calculate maximum number of anagrams
	max = calcMax(anagrams, SIZE);

	// Calculate the number of lines with max number of anagrams
	for(i = 0; i < SIZE; i++) {
		if(anagrams[i].n == max) {
			most++;
			positions = realloc(positions, sizeof(int) * most);
			positions[most-1] = i; // Keep the positions
		}
	}

	// Sorting rows of anagrams
	for(i = 0; i < most; i++) {
		for(j = 1; j < most-i; j++) {
			if(strcmp(anagrams[positions[j]].q[0], anagrams[positions[j-1]].q[0]) < 0)
				swapPos(positions, j, j-1); // swap positions only
		}
	}

	// Give answer
	printf("%d\n", most);
	for(i = 0; i < most; i++) {
		for(j = 0; j < anagrams[positions[i]].n-1; j++) {
			printf("%s, ", anagrams[positions[i]].q[j]);
		}
		printf("%s\n", anagrams[positions[i]].q[j]);
	}


	// Freeing
 	fclose(fp);
	free(filename);
	free(positions);
	for(i = 0; i < SIZE; i++) {
		for(j = 0; j < anagrams[i].n; j++) free(anagrams[i].q[j]);
		free(anagrams[i].q);
	}
	free(anagrams);
	return 0;
}

