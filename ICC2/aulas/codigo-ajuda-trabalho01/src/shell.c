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
	} while (c != DELIMITER);

	line = (char *) realloc(line, sizeof(char) * (counter+1));
	line[counter++] = '\0';

	return line;
}

BOOLEAN create_table(char *cmd) {
	int i;
	char **s;

	s = match(cmd, "^\\s*create\\s+table\\s+([^\\s]*)\\s+\\((.*)\\)\\s*;$", 3);
	// s[0] = "create table PERSON (code int, name char[80], age int, salary double);"
	// s[1] = "PERSON"
	// s[2] = "code int, name char[80], age int, salary double"
	if (s != NULL) {

		printf("Creating table '%s'\n", s[0]);
		printf("Creating table '%s'\n", s[1]);
		printf("Creating table '%s'\n", s[2]);

		tableList = (TABLE **) realloc(tableList, 
				sizeof(TABLE *) * (tableCounter+1));
		tableList[tableCounter] = (TABLE *) malloc(sizeof(TABLE));
		tableList[tableCounter]->tablename = (char *)
				malloc(sizeof(char) * (strlen(s[1])+1));
		strcpy(tableList[tableCounter]->tablename, s[1]);
		tableList[tableCounter]->fields = NULL;
		tableList[tableCounter]->fieldCounter = 0;

		// Descobrir os campos???
		// s[2] = "code int, name char[80], age int, salary double"
		token = strtok(s[2], ",");
		while (token != NULL) {

			// processar... fmd = field metadata
			fmd = match(token, "^\\s*([^\\s]*)\\s+([^\\s]*)\\s*$", 3);
			// fmd[1] = "code"
			// fmd[2] = "int"

			tableList[tableCounter]->fields = (TABLE_FIELD **)
				realloc(tableList[tableCounter]->fields,
					sizeof(TABLE_FIELD *) * 
					 (tableList[tableCounter]->fieldCounter+1));
			tableList[tableCounter]->fields[
				tableList[tableCounter]->fieldCounter] = 
				  (TABLE_FIELD *) malloc(sizeof(TABLE_FIELD));

			tableList[tableCounter]->fields[
				tableList[tableCounter]->fieldCounter]->fieldname =
					(char *) malloc(sizeof(char) * 
							(strlen(fmd[1])+1));
			strcpy(tableList[tableCounter]->fields[
				tableList[tableCounter]->fieldCounter]->fieldname,
					fmd[1]);
			if (strcmp(fmd[2], "int") == 0) {
			   tableList[tableCounter]->fields[
				tableList[tableCounter]->fieldCounter]->fieldtype =
					INT;
			} else if (strcmp(fmd[2], "double") == 0) {
			   tableList[tableCounter]->fields[
				tableList[tableCounter]->fieldCounter]->fieldtype =
					DOUBLE;
			} else if (strcmp(fmd[2], "char") == 0) {
			   tableList[tableCounter]->fields[
				tableList[tableCounter]->fieldCounter]->fieldtype =
					CHAR;
			}
			tableList[tableCounter]->fieldCounter++;
			
			token = strtok(NULL, ",");
		}
		tableCounter++;

		for (i = 0; i < 3; i++) free(s[i]);
		free(s);
		return TRUE;
	}
	return FALSE;

}

BOOLEAN create_database(char *cmd) {
	int i;
	char **s;

	s = match(cmd, "^\\s*create\\s+database\\s+([^;]*);$", 2);
	// s[0] = "create database DB1;"
	// s[1] = "DB1"
	if (s != NULL) {

		printf("Creating database '%s'\n", s[1]);

		// criar um diretorio....
		if (!mkdir(s[1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) {
			printf("Successfully created.\n");
		} else {
			printf("Failed.\n");
		}

		for (i = 0; i < 2; i++) free(s[i]);
		free(s);
		return TRUE;
	}
	return FALSE;
}

BOOLEAN drop_database(char *cmd) {
	int i;
	char **s;

	s = match(cmd, "^\\s*drop\\s+database\\s+([^;]*);$", 2);
	// s[0] = "drop database DB1;"
	// s[1] = "DB1"
	if (s != NULL) {

		printf("Dropping database '%s'\n", s[1]);

		// removendo um diretorio....
		if (!rmdir(s[1])) {
			printf("Successfully dropped.\n");
		} else {
			printf("Failed.\n");
		}

		for (i = 0; i < 2; i++) free(s[i]);
		free(s);
		return TRUE;
	}
	return FALSE;
}

BOOLEAN connect_database(char *cmd) {
	int i;
	char **s;

	s = match(cmd, "^\\s*connect\\s+database\\s+([^;]*);$", 2);
	// s[0] = "connect database DB1;"
	// s[1] = "DB1"
	if (s != NULL) {
		printf("Connecting to database '%s'\n", s[1]);

		if (dbName != NULL) free(dbName);
		dbName = (char *) malloc(sizeof(char) * (strlen(s[1])+1));
		strcpy(dbName, s[1]);

		for (i = 0; i < 2; i++) free(s[i]);
		free(s);
		return TRUE;
	}
	return FALSE;
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
		if (create_database(cmd)) { continue; }
		if (connect_database(cmd)) { continue; }
		if (drop_database(cmd)) { continue; }
		if (create_table(cmd)) { continue; }

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
