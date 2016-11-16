#ifndef _HASH_H_
#define _HASH_H_

#define SIZE 300007


struct ANAGRAM {
	char **q;
	int n;
};

void swapPos(int *positions, int a, int b);
int calcMax(struct ANAGRAM *anagram, int n);
int test(char *string1, char *string2);
int hash(char *string, int n);

#endif
