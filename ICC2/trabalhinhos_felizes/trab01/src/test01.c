#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <regex.h>

#define CREATE "^\\s*create\\s+database\\s+([^;]*);$"

char **match(char *string, char *PATTERN, int nvars) {
	int retval;
	regex_t re;
	int i, start, len, counter = 0;
	regmatch_t *rm;
	char **allstrings = NULL;

	rm = (regmatch_t *) malloc(sizeof(regmatch_t) * nvars);

	if (regcomp(&re, PATTERN, REG_EXTENDED) != 0) {
		fprintf(stderr, "Failed to compile regex '%s'\n", PATTERN);
		return allstrings;
	}

	if ((retval = regexec(&re, string, nvars, rm, 0)) == 0) {
		for (i = 0; i < nvars; i++) {
			start = rm[i].rm_so;
			len = rm[i].rm_eo - rm[i].rm_so;
				printf("Start: %d End: %d Length: %d\n", 
						rm[i].rm_so, rm[i].rm_eo, len);

			allstrings = (char **) realloc(allstrings, 
					sizeof(char *) * (counter+1));
			allstrings[counter] = (char *) malloc(sizeof(char)*(len+1));
			memcpy(allstrings[counter], &string[start], len);
				allstrings[counter][len] = '\0';
			counter++;
		}
	} 

	return allstrings;
}

enum {
	PROGNAME,
	PATTERN,
	TEXT,
	NVARS,
	NARGS
};

int main(int argc, char **argv) {
	char **tokens;
	int i;

	if (argc != NARGS) {
		printf("usage: %s pattern text nvars\n", argv[PROGNAME]);
		return -1;
	}

	int nvars = atoi(argv[NVARS]);
	tokens = match(argv[TEXT], argv[PATTERN], nvars);

	if (tokens != NULL) {
		for (i = 0; i < nvars && tokens[i] != NULL; i++) {
			printf("%s\n", tokens[i]);
		}
	}

	return 0;
}
