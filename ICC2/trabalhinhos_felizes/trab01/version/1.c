#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <myregex.h>
#include <string.h>
#include <unistd.h>

#define DELIMITER ';'

typedef enum {
	INT,
	CHAR,
	DOUBLE,
	FLOAT
} FIELD_TYPE;

typedef struct {
	char *fieldname;
	FIELD_TYPE fieldtype;
	int size;
} TABLE_FIELD;

typedef struct {
	char *tablename;
	TABLE_FIELD **fields;
	int fieldCounter;
} TABLE;

typedef enum {
	FALSE,
	TRUE
} BOOLEAN;

// arghhhhhh
char *dbName = NULL;
TABLE **tableList = NULL;
int tableCounter = 0;

char *readLine(FILE *stream) {
	char *line = NULL;
	int counter = 0;
	char c;

	do {
		c = fgetc(stream);
		line = (char *) realloc(line, sizeof(char) * (counter+1));
		line[counter++] = c;
	} while (c != '\n');
	line[counter-1] = '\0';

	return line;
}

BOOLEAN create_table(char *cmd) {
	int i;
	char **s, **lurker, **fmd, *token;

	s = match(cmd, "^\\s*create\\s+table\\s+(.*)\\s+\\((.*)\\)\\s*;$", 3);
	// s[0] = "create table PERSON (code int, name char[80], age int, salary double);"
	// s[1] = "PERSON"
	// s[2] = "code int, name char[80], age int, salary double"
	if (s != NULL) {

		printf("Creating table '%s'\n", s[0]);
		printf("Creating table '%s'\n", s[1]);
		printf("Creating table '%s'\n", s[2]);

		tableList = (TABLE **) realloc(tableList, sizeof(TABLE *) * (tableCounter+1)); 			// aumenta um espaco para o ponteiro da nova tabela
		tableList[tableCounter] = (TABLE *) malloc(sizeof(TABLE)); 										// vai ateh o final da lista e aloca para a nova tabela
		tableList[tableCounter]->tablename = (char *) malloc(sizeof(char) * (strlen(s[1])+1));
		strcpy(tableList[tableCounter]->tablename, s[1]);

		/*Inicializando variaveis --> no trash here b*tch*/
		tableList[tableCounter]->fields = NULL;
		tableList[tableCounter]->fieldCounter = 0;
		// Descobrir os campos???
		// s[2] = "code int, name char[80], age int, salary double"
		token = strtok(s[2], ",");
		while (token != NULL) {

			// processar... fmd = field metadata
			fmd = match(token, "^\\s*(.*)\\s+(.*)\\s*$", 3);
			// fmd[1] = "code"
			// fmd[2] = "int"
			lurker = match(fmd[2], "^char\\[(.*)\\]$", 2);

			tableList[tableCounter]->fields=(TABLE_FIELD **)realloc(tableList[tableCounter]->fields,sizeof(TABLE_FIELD*)*(tableList[tableCounter]->fieldCounter+1));
			tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter] = (TABLE_FIELD *) malloc(sizeof(TABLE_FIELD));

			tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldname = (char *) malloc(sizeof(char) * (strlen(fmd[1])+1));
			strcpy(tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldname,fmd[1]);

			/*Escolhendo o tipo da variavel, e determinando seu tamanho*/
			if (strcmp(fmd[2], "int") == 0) {
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldtype = INT;
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->size = sizeof(int);

			} else if (strcmp(fmd[2], "double") == 0) {
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldtype = DOUBLE;
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->size = sizeof(double);

			} else if (strcmp(fmd[2], "char") == 0) {
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldtype = CHAR;
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->size = sizeof(char);

			} else if(lurker != NULL){ 						// aoooooo eh uma fucking string b*tch
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldtype = CHAR;
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->size = sizeof(char)*(atoi(lurker[1])); //colocando o tamanho de toda a string
				for(i = 0; i < 2; i++) free(lurker[i]);
				free(lurker);
			}

			tableList[tableCounter]->fieldCounter++;
			token = strtok(NULL, ",");
			for(i = 0; i < 3; i++) free(fmd[i]);
			free(fmd);
		}
		tableCounter++;

		/*Libera tudo*/
		for (i = 0; i < 3; i++) free(s[i]);
		free(s);
		free(token);
		return TRUE;
	}
	return FALSE;

}


BOOLEAN insert(char *cmd) {
	char **s;
	FILE *fp;
	int i;
	s = match(cmd, "^\\s*insert\\s+into\\s+(.*)\\s+\\((.*)\\)\\s+values\\s+\\((.*)\\);$", 4);
	if(s != NULL){
		s[1] = (char*) realloc(s[1], sizeof(char)*(strlen(s[1])+4));
		strcat(s[1], ".tmp"); // works
		fp = fopen(s[1], "a+");
		fprintf(fp, "%s\n", s[3]);
		fclose(fp);
		return TRUE;
	}
	return FALSE;
}

BOOLEAN showalltables(char *cmd) {
	char **s;
	int i, j;
	s = match(cmd, "^showalltables$", 1);
	if(s != NULL){
		for(j = 0; j < tableCounter; j++)
		printf("\nTablename: %s\n", tableList[j]->tablename);
		for(i = 0; i < tableList[j]->fieldCounter; i++){
			if(tableList[j]->fields[i]->fieldtype == INT)
				printf("\tField: %s Type: %s Size: %d\n", tableList[j]->fields[i]->fieldname, "int", tableList[j]->fields[i]->size);

			else if(tableList[j]->fields[i]->fieldtype == DOUBLE)
				printf("\tField: %s Type: %s Size: %d\n", tableList[j]->fields[i]->fieldname, "double", tableList[j]->fields[i]->size);

			else if(tableList[j]->fields[i]->fieldtype == FLOAT)
				printf("\tField: %s Type: %s Size: %d\n", tableList[j]->fields[i]->fieldname, "float", tableList[j]->fields[i]->size);

			else if(tableList[j]->fields[i]->fieldtype == CHAR)
				printf("\tField: %s Type: %s Size: %d\n", tableList[j]->fields[i]->fieldname, "char", tableList[j]->fields[i]->size);
		}
		printf("\n");
		return TRUE;
	}
	return FALSE;
}

BOOLEAN showallindexes(char *cmd) {
	char **s;
	s = match(cmd, "^showallindexes$", 1);
	if(s != NULL){

		return TRUE;
	}
}

BOOLEAN quit(char *cmd) {
	int i;
	char **s;
	// cmd = "quit;"
	// s[0] = "quit;"

	s = match(cmd, "^\\s*quit\\s*;", 1);
	if (s != NULL) {
		for (i = 0; i < 1; i++) free(s[i]);
		free(s);
		return TRUE;
	}
	return FALSE;
}

void  shell(FILE *stream) {
	char *cmd;

	printf(">> Type your destiny...\n");
	while (TRUE) {
		printf(">> ");
		cmd = readLine(stream);
		//printf("Echo: %s\n", cmd);

		if (quit(cmd)) { break; }
		if (create_table(cmd)) { continue; }
		if (insert(cmd)) { continue; }
		if (showalltables(cmd)) { continue; }
		if (showallindexes(cmd)) { continue; }

		/*
		 drop_table(cmd)
		 create_index(cmd)
		 drop_index(cmd)
		 select(cmd)
		 */
	}
}

int main(int argc, char *argv[]) {

	shell(stdin);

	return 0;
}
