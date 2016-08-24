#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <myregex.h>
#include <string.h>
#include <unistd.h>

#define DELIMITER ';'

/*Estruturas do SGBD*/
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

typedef struct{
	char *tableName;
	char *fieldName;
} INDEX;


typedef struct {
	char *tablename;
	TABLE_FIELD **fields;
	int fieldCounter;
	int elements;
} TABLE;

typedef enum {
	FALSE,
	TRUE
} BOOLEAN;
/*----------------*/

char *dbName = NULL;
TABLE **tableList = NULL;
int tableCounter = 0;
INDEX **indexList = NULL;


/*Variaveis para statistics*/
int ntables = 0, ninserts = 0, nindexes = 0, nselects = 0, nsorts = 0, nshowalltables = 0, nshowallindexes = 0,
recordsInLastSelectBinary = 0, recordsInLastSelectSequential = 0;
/*-------------------------*/



void sortINT(int *rows, int *data, int n){
	int i, j, aux;
	for(i = 0; i < n; i++)
		for(j = 1; j < n; j++){
			if(data[j] < data[j-1]){
				aux = data[j];
				data[j] = data[j-1];
				data[j-1] = aux;

				aux = rows[j];
				rows[j] = rows[j-1];
				rows[j-1] = aux;
			}
		}
}

void sortDOUBLE(int *rows, double *data, int n){
	int i, j, aux;
	double aux1;
	for(i = 0; i < n; i++)
		for(j = 1; j < n; j++){
			if(data[j] < data[j-1]){
				aux1 = data[j];
				data[j] = data[j-1];
				data[j-1] = aux1;

				aux = rows[j];
				rows[j] = rows[j-1];
				rows[j-1] = aux;
			}
		}
}

void sortCHAR(int *rows, char **data, int n){
	int i, j, aux;
	char *aux1;
	for(i = 0; i < n; i++)
		for(j = 1; j < n; j++){
			if(strcmp(data[j], data[j-1]) < 0){
				aux1 = data[j];
				data[j] = data[j-1];
				data[j-1] = aux1;

				aux = rows[j];
				rows[j] = rows[j-1];
				rows[j-1] = aux;
			}
		}
}


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

/*Função para criar tabelas*/
BOOLEAN create_table(char *cmd) {
	int i;
	char **s, **ifString, **fmd, *token;

	s = match(cmd, "^\\s*create\\s+table\\s+(.*)\\s+\\((.*)\\)\\s*;$", 3);
	// s[0] = "create table PERSON (code int, name char[80], age int, salary double);"
	// s[1] = "PERSON"
	// s[2] = "code int, name char[80], age int, salary double"
	if (s != NULL) {
		ntables++; //---> para statistics

		/*Alocando e inserindo o nome da tabela*/
		tableList = (TABLE **) realloc(tableList, sizeof(TABLE *) * (tableCounter+1));
		tableList[tableCounter] = (TABLE *) malloc(sizeof(TABLE));
		tableList[tableCounter]->tablename = (char *) malloc(sizeof(char) * (strlen(s[1])+1));
		strcpy(tableList[tableCounter]->tablename, s[1]);
		/*------------------------------------ */


		/*Inicializando variaveis*/
		tableList[tableCounter]->fields = NULL;
		tableList[tableCounter]->fieldCounter = 0;
		/*-----------------------*/


		/*Lendo campos => strtok*/
		token = strtok(s[2], ",");
		while (token != NULL) {

			fmd = match(token, "^\\s*(.*)\\s+(.*)\\s*$", 3);
			// fmd[1] = "code"
			// fmd[2] = "int"
			ifString = match(fmd[2], "^char\\[(.*)\\]$", 2); // Se for string, recuperar o tamanho

			/*Aumenta um espaço para o field lido*/
			tableList[tableCounter]->fields=(TABLE_FIELD **)realloc(tableList[tableCounter]->fields,sizeof(TABLE_FIELD*)*(tableList[tableCounter]->fieldCounter+1));
			tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter] = (TABLE_FIELD *) malloc(sizeof(TABLE_FIELD));
			/*-----------------------------------*/

			/*Aloca e insere o nome do field*/
			tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldname = (char *) malloc(sizeof(char) * (strlen(fmd[1])+1));
			strcpy(tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldname,fmd[1]);
			/*------------------------------*/

			/*Escolhendo o tipo da variavel, e determinando seu tamanho*/
			if (strcmp(fmd[2], "int") == 0) {
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldtype = INT;
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->size = sizeof(int);

			} else if (strcmp(fmd[2], "double") == 0) {
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldtype = DOUBLE;
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->size = sizeof(double);

			} else if (strcmp(fmd[2], "float") == 0) {
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldtype = FLOAT;
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->size = sizeof(float);

			} else if (strcmp(fmd[2], "char") == 0) {
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldtype = CHAR;
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->size = sizeof(char);

			} else if(ifString != NULL){ 						// Trata-se de string
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->fieldtype = CHAR;
			   tableList[tableCounter]->fields[tableList[tableCounter]->fieldCounter]->size = sizeof(char)*(atoi(ifString[1])); //colocando o tamanho de toda a string
				for(i = 0; i < 2; i++) free(ifString[i]);
				free(ifString);
			}

			/*Atualiza o contador dos campos (fieldCounter)*/
			tableList[tableCounter]->fieldCounter++;
			token = strtok(NULL, ",");
			/*---------------------------------------------*/

			for(i = 0; i < 3; i++) free(fmd[i]);
			free(fmd);
		}
		/*Atualiza tableCounter*/
		tableCounter++;

		/*Libera tudo*/
		for (i = 0; i < 3; i++) free(s[i]);
		free(s);
		free(token);
		return TRUE;
	}
	return FALSE;

}

/*Função para criar arquivo ordenado de acordo com campo de escolha do usuário (index)*/
BOOLEAN create_index(char *cmd){
	char **s, **lines, *tmp, *dat, c, *idx, *token, **p;
	int i = 0, tokenCounter = 0, table, j = 0;
	int *rows;
	double *typeD;
	int *typeI;
	char **typeC;



	FILE *fp, *fp1, *fp2;
	s = match(cmd, "^\\s*create\\s+index\\s*(.*)\\((.*)\\);$", 3);
	// s[1] => tablename
	// s[2] => campo

	if(s != NULL){

		nindexes++; //---> para statistics

		/*Para ShowAllIndexes*/
		indexList = realloc(indexList, sizeof(INDEX)*(nindexes));
		strcpy(indexList[nindexes-1]->tableName, s[1]);
		strcpy(indexList[nindexes-1]->fieldName, s[2]);

		/*-------------------*/
		/*Copiadno de tmp para dat*/
		tmp = (char*) malloc(sizeof(char)*(strlen(s[1])+4));
		dat = (char*) malloc(sizeof(char)*(strlen(s[1])+4));
		idx = (char*) malloc(sizeof(char)*(strlen(s[1])+5+strlen(s[2])));


		/*Gerando nomes dos arquivos*/
		strcpy(tmp, s[1]);
		strcpy(dat, s[1]);
		strcpy(idx, s[1]);

		strcat(tmp, ".tmp");
		strcat(dat, ".dat");
		strcat(idx, "-");
		strcat(idx, s[2]);
		strcat(idx, ".idx");
		/*-------------------------*/

		/*Abrindo arquivos .tmp .dat e .idx*/
		fp = fopen(tmp, "a+");
		fp1 = fopen(dat, "a+");
		fp2 = fopen(idx, "w+"); // Sempre trunca idx
		/*---------------------------------*/


		/*Copiando de tmp para dat*/
		while(!feof(fp)){
			fscanf(fp, "%c", &c);
			if(!feof(fp))
				fprintf(fp1, "%c", c);
		}
		/*-----------------------*/


		/*Descobrir as posicoes da tabela e do campo que procuramos, respectivamente*/
		for(table = 1; strcmp(tableList[table-1]->tablename, s[1]); table++); // Para quando achar a table de nome s[1]
		for(tokenCounter = 1; strcmp(tableList[table-1]->fields[tokenCounter-1]->fieldname, s[2]) != 0; tokenCounter++); // Para quando achar o campo de nome s[2]
		/*--------------------------------------------------------------------------*/


		/*Copiando de dat para idx*/
		fseek(fp1, 0, SEEK_SET);
		lines = (char**) malloc(sizeof(char*)*tableList[table-1]->elements); // Cada linha é um elemento da tabela
		rows = (int*) malloc(sizeof(int)*tableList[table-1]->elements);
		for(i = 0; i < tableList[table-1]->elements; i++) rows[i] = i+1;



		switch(tableList[table-1]->fields[tokenCounter-1]->fieldtype){
			case INT:
				typeI = (int*) malloc(sizeof(int)*tableList[table-1]->elements);
				for(i = 0; i < tableList[table-1]->elements; i++){
					lines[i] = readLine(fp1);

					/*Percorrendo até o token que queremos*/
					token = strtok(lines[i], ",");
					for(j = 0; j < tokenCounter-1; j++)
						token = strtok(NULL, ",");
					/*------------------------------------*/

					/*Trata eventuais espaços indesejados e escreve em .idx*/
					p = match(token, "^\\s*(.*)\\s*$", 2);
					typeI[i] = atoi(p[1]);
					/*-----------------------------------------------------*/
				}

				sortINT(rows, typeI, tableList[table-1]->elements);
				for(i = 0; i < tableList[table-1]->elements; i++)
					fprintf(fp2, "%d %d\n", rows[i], typeI[i]);
				free(typeI);
				break;

			case DOUBLE:
			case FLOAT:
				typeD = (double*) malloc(sizeof(double)*tableList[table-1]->elements);
				for(i = 0; i < tableList[table-1]->elements; i++){
					lines[i] = readLine(fp1);

					/*Percorrendo até o token que queremos*/
					token = strtok(lines[i], ",");
					for(j = 0; j < tokenCounter-1; j++)
						token = strtok(NULL, ",");
					/*------------------------------------*/

					/*Trata eventuais espaços indesejados e escreve em .idx*/
					p = match(token, "^\\s*(.*)\\s*$", 2);
					typeD[i] = atof(p[1]);
					/*-----------------------------------------------------*/
				}

				sortDOUBLE(rows, typeD, tableList[table-1]->elements);
				for(i = 0; i < tableList[table-1]->elements; i++)
					fprintf(fp2, "%d %lf\n", rows[i], typeD[i]);
				free(typeD);
				break;


			case CHAR:
				typeC = (char**) malloc(sizeof(char*)*tableList[table-1]->elements);
				for(i = 0; i < tableList[table-1]->elements; i++){
					lines[i] = readLine(fp1);

					/*Percorrendo até o token que queremos*/
					token = strtok(lines[i], ",");
					for(j = 0; j < tokenCounter-1; j++)
						token = strtok(NULL, ",");
					/*------------------------------------*/

					/*Trata eventuais espaços indesejados e escreve em .idx*/
					p = match(token, "^\\s*(.*)\\s*$", 2);
					typeC[i] = p[1];
					/*-----------------------------------------------------*/
				}

				sortCHAR(rows, typeC, tableList[table-1]->elements);
				for(i = 0; i < tableList[table-1]->elements; i++)
					fprintf(fp2, "%d %s\n", rows[i], typeC[i]);

				for(i = 0; i < tableList[table-1]->elements; i++) free(typeC[i]);
				free(typeC);
				break;
		}



		/*Removendo tmp, liberando heap e fechando arquivos*/
		remove(tmp);

		free(tmp);
		free(dat);
		free(idx);
		free(rows);
		for(i = 0; i < 3; i++) free(s[i]);
		free(s);
		for(i = 0; i < tableList[table-1]->elements; i++) free(lines[i]);
		free(lines);

		fclose(fp);
		fclose(fp1);
		fclose(fp2);
		/*------------------------------------------------*/

		return TRUE;
	}
	return FALSE;
}

/*Função para inserir um elemento em uma determinada tabela*/
BOOLEAN insert(char *cmd) {
	char **s, *aux;
	FILE *fp;
	int i;

	/*Recupera o nome da tabela, os campos e os respectivos valores*/
	s = match(cmd, "^\\s*insert\\s+into\\s+(.*)\\s+\\((.*)\\)\\s+values\\s+\\((.*)\\);$", 4);
	/*-------------------------------------------------------------*/

	if(s != NULL){

		ninserts++; //---> para statistics

		/*Gerando nome e criando o arquivo .tmp*/
		aux = (char*) malloc(sizeof(char)*(strlen(s[1])+5));
		strcpy(aux, s[1]); // Copiar para não alterar s[1]
		strcat(aux, ".tmp");
		fp = fopen(aux, "a+");
		fprintf(fp, "%s\n", s[3]);
		fclose(fp);
		/*-------------------------------------*/

		/*Incrementando elements*/
		for(i = 0; i < tableCounter; i++){
			if(strcmp(tableList[i]->tablename, s[1]) == 0){
				tableList[i]->elements++;
				break;
			}
		}
		/*---------------------*/


		for(i = 0; i < 4; i++) free(s[i]);
		free(s);
		free(aux);
		return TRUE;
	}
	return FALSE;
}

BOOLEAN selector(char *cmd) {
	char **s, **p, **values;
	char *tmp, *idx, *string;
	int i, mid, end, start;
	s = match(cmd, "^\\s*select\\s+(.*)\\s+(.*)\\s+(.*)\\s*;$", 4);
	// s[1] -> tabela
	// s[2] -> campo
	// s[3] -> valor
	if(s != NULL){

		recordsInLastSequntial = 0;
		recordsInLastBinary = 0;
		tmp = (char*) malloc(sizeof(char)*(strlen(s[1])+4));
		idx = (char*) malloc(sizeof(char)*(strlen(s[1])+5+strlen(s[2])));


		/*Gerando nomes dos arquivos*/
		strcpy(tmp, s[1]);
		strcpy(idx, s[1]);

		strcat(tmp, ".tmp");
		strcat(idx, "-");
		strcat(idx, s[2]);
		strcat(idx, ".idx");
		/*-------------------------*/
		fp = fopen(idx, "r");
		fp1 = fopen(tmp, "r");


		/*Sequential Search*/
		while(!feof(tmp)){
			string = readLine(tmp);
			if(feof(tmp)) break;
			p = match(string, "^(.*)\\s+(.*)$", 3);

			if(strcmp(p[2], s[3]) == 0){ 	// Achei
				printf("linha do .dat = %s\n", p[1]);
				recordsInLastSequential++;
			}

			for(i = 0; i < 3; i++) free(p[i]);
			free(p);
			free(string);
		}
		/*-----------------*/


		for(end = 0; !feof(idx); end++){
			string = readLine(idx);

			if(feof(idx)) break;

			values = (char **) realloc(values, sizeof(char *)*(end+1)); // coloca a string inteira na matriz
			values[end] = string;
		}



		/*Binary Search*/
		start = 0//	comeco do vetor
		while(end >= start){
			p = match(values[mid], "^(.*)\\s+(.*)\\s*$", 2);

			mid = (end + start)/2;
			if(strcmp(, s[3]) == 0) break;
			else if(strcmp(values[mid], s[3]) > 0) end = mid-1;
			else start = mid+1;
		}
		/*-------------*/

		fclose(fp);
		fclose(fp1);
		free(tmp);
		free(idx);
		for(i = 0; i < 4; i++) free(s[i]);
		free(s);
		return TRUE;
	}
	for(i = 0; i < 4; i++) free(s[i]);
	free(s);
	return FALSE;

}

BOOLEAN sort(char *cmd) {
	char **s, *string;
	int i;
	s = match(cmd, "^\\s*sort\\s+(.*)$", 2);
	//s[1] -> tabela(campo)
	if(s != NULL){

		string = malloc(sizeof(char)*(strlen(s[1])+15));
		strcpy(string, "create index ");
		strcat(string, s[1]);
		create_index(string);

		free(string);
		for(i = 0; i < 3; i++) free(s[i]);
		free(s);
		return TRUE;
	}

	for(i = 0; i < 3; i++) free(s[i]);
	free(s);
	return FALSE;
}

/*Função para mostrar todas as tabelas*/
BOOLEAN showalltables(char *cmd) {
	char **s;
	int i, j;
	s = match(cmd, "^showalltables[;]$", 1);
	if(s != NULL){
		nshowalltables++;
		for(j = 0; j < tableCounter; j++){
			printf("\nTablename: %s\n", tableList[j]->tablename);

			for(i = 0; i < tableList[j]->fieldCounter; i++){
				/*Escolhendo o tipo de dado*/
				switch(tableList[j]->fields[i]->fieldtype){
					case INT:
						printf("\tField: %s Type: %s Size: %d\n", tableList[j]->fields[i]->fieldname, "int", tableList[j]->fields[i]->size);
						break;
					case DOUBLE:
						printf("\tField: %s Type: %s Size: %d\n", tableList[j]->fields[i]->fieldname, "double", tableList[j]->fields[i]->size);
						break;
					case FLOAT:
						printf("\tField: %s Type: %s Size: %d\n", tableList[j]->fields[i]->fieldname, "float", tableList[j]->fields[i]->size);
						break;
					case CHAR:
						printf("\tField: %s Type: %s Size: %d\n", tableList[j]->fields[i]->fieldname, "char", tableList[j]->fields[i]->size);
						break;
				}
			}
		}
		printf("\n");
		return TRUE;
	}
	return FALSE;
}

BOOLEAN showallindexes(char *cmd) {
	char **s;
	int i;
	s = match(cmd, "^showallindexes[;]$", 1);
	if(s != NULL){
		nshowallindexes++;
		// deve estar na ordem de criaçao dos ı́ndices
		for (i = 0; i < nindexes; i++){
			printf("\nIndex information\n");
			// nome da tabela relacionada ao ı́ndice i
			printf("\tTablename: %s\n", indexList[i]->tableName);
			// nome do campo indexado
			 printf("\tFieldname: %s\n\n", indexList[i]->fieldName);
			}
		return TRUE;
	}
	return FALSE;
}

BOOLEAN statistics(char *cmd) {
	char **s;
	s = match(cmd, "^statistics[;]$", 1);
	if(s != NULL){
		printf("#Tables: %d\n", ntables);
		printf("#Indexes: %d\n", nindexes);
		printf("#Inserts: %d\n", ninserts);
		printf("#Selects: %d\n", nselects);
		printf("#Sorts: %d\n", nsorts);
		printf("#ShowAllTables: %d\n", nshowalltables);
		printf("#ShowAllIndexes: %d\n", nshowallindexes);
		printf("#Records in last select (binary search): %d\n", recordsInLastSelectBinary);
		printf("#Records in last select (sequential search): %d\n", recordsInLastSelectSequential);

		return TRUE;
	}
	return FALSE;
}

BOOLEAN quit(char *cmd) {
	int i;
	char **s;

	s = match(cmd, "^\\s*quit\\s*;", 1);
	if (s != NULL) {
		/*Free showalltables*/
		/*------------------*/
		/*Free showallindexes*/
		/*-------------------*/
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

		if (quit(cmd)) { break; }
		if (create_table(cmd)) { continue; }
		if (create_index(cmd)) { continue; }
		if (insert(cmd)) { continue; }
		if (selector(cmd)) { continue; }
		if (sort(cmd)) { continue; }
		if (showalltables(cmd)) { continue; }
		if (showallindexes(cmd)) { continue; }
		if (statistics(cmd)) { continue; }


	}
}

int main(int argc, char *argv[]) {

	shell(stdin);

	return 0;
}
