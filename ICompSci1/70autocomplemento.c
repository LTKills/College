#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

char *readLine(FILE *fp){
	char *string = NULL;
	char c;
	int i = 0;

	do{

		c = fgetc(fp);
		string = realloc(string, sizeof(char)*(i+1));
		string[i++] = c;

	}while(c != 10);
	string[i-1] = '\0';

	return string;
}


typedef struct{
	int freq;
	char name[50];
} word;


int main(int argc, char *argv[]){
	char file[5000];
	FILE *query = NULL, *dic = NULL;
	word *dict, aux;
	int d = 0, q = 0, i, j, k = 0, f;

	scanf("%s", file);
	dic = fopen(file, "r");

	scanf("%s", file);
	query = fopen(file, "r");

	while(!feof(dic)){
		dict = realloc(dict, sizeof(word)*(d+1));
		fscanf(dic, "%s %d", dict[d].name, &dict[d].freq);
		//printf("%s %d\n", dict[d].name, dict[d].freq);
		d++;
	}

	while(!feof(query)){
		fscanf(query, "%c", &file[q++]);
		if(!feof(query))
			fgetc(query);
	}


	for(k = 1; k < d; k++){ // i = k; j = f
		aux = dict[k];
		f = k - 1;
		while((f >= 0) && (aux.freq > dict[f].freq)){
			dict[f+1] = dict[f];
			f--;
		}
		dict[f+1] = aux;
	}

	for(i = 0; i < q; i++){
		k = 0;
		for(j = 0; j < d && k < 5; j++){
			if(!strncmp(file, dict[j].name, i+1)){ // DEU MATCH PORRA!
				printf("%s ", dict[j].name);
				k++;
			}
		}
		if(k != 0)
			printf("\n");
		if(k == 1) break;
	}

	free(dict);
	fclose(dic);
	fclose(query);
	return 0;
}
