#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <myregex.h>
#include <string.h>
#include <unistd.h>
#include <structs.h>

TABLE **tableList = NULL;
int tableCounter = 0;
INDEX *indexList = NULL;

char *readLine(FILE *stream) {
	char *line = NULL;
	int counter = 0;
	char c;

	do {
		c = fgetc(stream);
		line = (char *) realloc(line, sizeof(char) * (counter+1));
		line[counter++] = c;
	} while (c != '\n' && c != EOF);
	line[counter-1] = '\0';

	return line;
}

/*Imprime uma linha desejada do arquivo .dat*/
void printDatLine(FILE *dat, int line){
	int i;
	char *string;
	fseek(dat, 0, SEEK_SET);

	for(i = 0; i < line-1; i++){
	   	string = readLine(dat);
		free(string);
	}

	string = readLine(dat);
	printf("%s\n", string);
	free(string);
}
/*------------------------------------------*/

/*Carrega o arquivo .idx em uma matriz na heap*/
char **load(FILE *fp, int *rows){
	char **file = NULL, *line;
	int i = 0;

	fseek(fp, 0, SEEK_SET);
	while(!feof(fp)){

		if(fgetc(fp) == EOF) break;
		fseek(fp, -1, SEEK_CUR);
		line = readLine(fp);
		file = (char **) realloc(file, sizeof(char*)*(i+1));
		file[i] = line;
		i++;

	}

	*rows = i-1;

	return file;
}
/*-------------------------------------------*/

/*Busca sequencial no arquivo tmp*/
int seqSearch(FILE *fp, int tokenCounter, FIELD_TYPE type, char *look, VARS *global){
	char **s, *token, *string, *copy;
	int j, founds = 0, i;


	fseek(fp, 0, SEEK_SET);
	while(!feof(fp)){


		if(fgetc(fp) == EOF) break;
		fseek(fp, -1, SEEK_CUR);
		string = readLine(fp);
		copy = (char *) malloc(sizeof(char)*(strlen(string)+1));
		strcpy(copy, string);


		/*Percorrendo até o token que queremos*/
		token = strtok(copy, ",");
		for(j = 0; j < tokenCounter-1; j++)
			token = strtok(NULL, ",");
		/*------------------------------------*/

		/*Trata eventuais espaços indesejados*/
		s = match(token, "^\\s*(.*)\\s*$", 2);
		if(type == CHAR)
			s = match(token, "^\\s*'(.*)'\\s*$", 2);
		/*-----------------------------------*/
		if(strcmp(s[1], look) == 0){
			global->recordsInLastSequential++;
			printf("%s\n", string);
			founds++;
		}

		for(i = 0; i < 2; i++)free(s[i]);
		free(s);
		free(string);
		free(copy);
	}
	return founds;
}


/*Faz uma busca sequencial na vizinhança de mid para o caso em que há valores repetidos*/
void binSeq(int mid, int last, char *look, FIELD_TYPE type, char **idxMat, FILE *dat, VARS *global){
	int start = mid-1, end = mid + 1, i, j;
	char **s;

	if(start < 0 || end > last){ // se estou no começo ou fim do vetor

		switch(type){
			case INT:
				s = match(idxMat[mid], "^\\s*(.*)\\s+(.*)\\s*$", 3);
				if(atoi(s[1]) == atoi(look)){
					global->recordsInLastBinary++;
					printDatLine(dat, atoi(s[2]));
					return;
				}
				//printf("null\n");
				break;
			case FLOAT:
			case DOUBLE:
				s = match(idxMat[mid], "^\\s*(.*)\\s+(.*)\\s*$", 3);
				if(atof(s[1]) == atof(look)){
					global->recordsInLastBinary++;
					printDatLine(dat, atoi(s[2]));
					return;
				}
				//printf("null\n");
				break;
			case CHAR:
				s = match(idxMat[mid], "^\\s*'(.*)'\\s+(.*)\\s*$", 3);
				if(strcmp(s[1], look) == 0){
					global->recordsInLastBinary++;
					printDatLine(dat, atoi(s[2]));
					return;
				}
				//printf("null\n");
				break;
		}
		return; // evita de entrar no outro caso (economizei um else)
	}

	//  Grande mellão
	// ^ Easter egg ^

	/*Caso eu não esteja no começo ou final do vetor*/
	switch(type){

		case CHAR:
			s = match(idxMat[start], "^\\s*(.*)\\s+(.*)\\s*$", 3);
			for(start = mid-1; (strcmp(look, s[1]) == 0) && start >= 0; start--){
				for(i = 0; i < 3; i++) free(s[i]);
				free(s);
				s = match(idxMat[start], "^\\s*(.*)\\s+(.*)\\s*$", 3);
				if(strcmp(s[1], look) != 0) break;
			}
			for(i = 0; i < 3; i++) free(s[i]);
			free(s);

			s = match(idxMat[end], "^\\s*(.*)\\s+(.*)\\s*$", 3);
			for(end = mid+1; (strcmp(look, s[1]) == 0) && end <= last; end++){
				for(i = 0; i < 3; i++) free(s[i]);
				free(s);
				s = match(idxMat[end], "^\\s*(.*)\\s+(.*)\\s*$", 3);
				if(strcmp(s[1], look) != 0) break;
			}
			for(i = 0; i < 3; i++) free(s[i]);
			free(s);
			break;

		case INT:
			s = match(idxMat[start], "^\\s*(.*)\\s+(.*)\\s*$", 3);
			for(start = mid-1; atoi(look) == atoi(s[1]) && start >= 0; start--){
				for(i = 0; i < 3; i++) free(s[i]);
				free(s);
				s = match(idxMat[start], "^\\s*(.*)\\s+(.*)\\s*$", 3);
				if(atoi(s[1]) != atoi(look)) break;
			}
			for(i = 0; i < 3; i++) free(s[i]);
			free(s);

			s = match(idxMat[end], "^\\s*(.*)\\s+(.*)\\s*$", 3);
			for(end = mid+1; (atoi(look) == atoi(s[1])) && end <= last; end++){
				for(i = 0; i < 3; i++) free(s[i]);
				free(s);
				s = match(idxMat[end], "^\\s*(.*)\\s+(.*)\\s*$", 3);
				if(atoi(s[1]) != atoi(look)) break;
			}
			for(i = 0; i < 3; i++) free(s[i]);
			free(s);
			break;

		case FLOAT:
		case DOUBLE:
			s = match(idxMat[start], "^\\s*(.*)\\s+(.*)\\s*$", 3);
			for(start = mid-1; atof(look) == atof(s[1]) && start >= 0; start--){
				for(i = 0; i < 3; i++) free(s[i]);
				free(s);
				s = match(idxMat[start], "^\\s*(.*)\\s+(.*)\\s*$", 3);
				if(atof(s[1]) != atof(look)) break;
			}
			for(i = 0; i < 3; i++) free(s[i]);
			free(s);

			s = match(idxMat[end], "^\\s*(.*)\\s+(.*)\\s*$", 3);
			for(end = mid+1; (atof(look) == atof(s[1])) && end <= last; end++){
				for(i = 0; i < 3; i++) free(s[i]);
				free(s);
				s = match(idxMat[end], "^\\s*(.*)\\s+(.*)\\s*$", 3);
				if(atof(s[1]) != atof(look)) break;
			}
			for(i = 0; i < 3; i++) free(s[i]);
			free(s);
			break;
	}

	for(i = start+1; i < end; i++){
		s = match(idxMat[i], "^\\s*(.*)\\s+(.*)\\s*$", 3);
		global->recordsInLastBinary++;
		printDatLine(dat, atoi(s[2]));
		for(j = 0; j < 3; j++) free(s[j]);
		free(s);
	}
}


/*Realiza busca binaria no arquivo idx*/
int binSearch(FILE *idx, FILE *dat, int tokenCounter, FIELD_TYPE type, char *look, VARS *global){
	char **s, **idxMat;
	int line = -1, start = 0, end, mid, last, i;

	idxMat = load(idx, &end);
	last = end;


	while(end >= start){
		mid = (end + start)/2;

		/*Escolhe o tipo do dado para fazer a busca*/
		switch(type){
			case INT:
				/*Pega o valor e a linha do .dat*/
				s = match(idxMat[mid], "^\\s*(.*)\\s+(.*)\\s*$", 3);
				/*------------------------------*/

				if(atoi(look) == atoi(s[1])){
				   	line = atoi(s[2]);
				}
				else if(atoi(look) > atoi(s[1])) start = mid+1;
				else end = mid-1;
				break;

			case FLOAT:
			case DOUBLE:

				/*Pega o valor e a linha do .dat*/
				s = match(idxMat[mid], "^\\s*(.*)\\s+(.*)\\s*$", 3);
				/*------------------------------*/

				if(atof(look) == atof(s[1])) line = atoi(s[2]);
				else if(atof(look) > atof(s[1])) start = mid+1;
				else end = mid-1;
				break;

			case CHAR:

				/*Pega o valor e a linha do .dat*/
				s = match(idxMat[mid], "^\\s*'(.*)'\\s+(.*)\\s*$", 3);
				/*------------------------------*/

				if(strcmp(s[1], look) == 0) line = atoi(s[2]);
				else if(strcmp(s[1], look) < 0) start = mid+1;
				else end = mid-1;
				break;
		}

		if(line != -1)
			break;
		for(i = 0; i < 3; i++) free(s[i]);
		free(s);
	}

	if(strcmp(s[1], look) == 0){ // Achei pelo menos 1
		binSeq(mid, last, look, type, idxMat, dat, global);
		return 1;
	}
	return 0; // Não achei nada
}




/*Ordena quando trata-se de INT*/
/*Yep, bubble sort :(*/
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

/*Ordena quando trata-se de DOUBLE*/
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

/*Ordena quando trata-se de CHAR*/
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


/*Função para criar tabelas*/
BOOLEAN create_table(char *cmd, VARS *global) {
	int i;
	char **s, **ifString, **fmd, *token, **d;

	s = match(cmd, "^\\s*create\\s+table\\s+(.*)\\s+\\((.*)\\)\\s*;$", 3);
	// s[0] = "create table PERSON (code int, name char[80], age int, salary double);"
	// s[1] = "PERSON"
	// s[2] = "code int, name char[80], age int, salary double"
	if (s != NULL) {
		global->ntables++; //---> para statistics

		/*Alocando e inserindo o nome da tabela*/
		tableList = (TABLE **) realloc(tableList, sizeof(TABLE *) * (tableCounter+1));
		tableList[tableCounter] = (TABLE *) malloc(sizeof(TABLE));
		tableList[tableCounter]->tablename = (char *) malloc(sizeof(char) * (strlen(s[1])+1));
		strcpy(tableList[tableCounter]->tablename, s[1]);
		/*------------------------------------ */


		/*Inicializando variaveis*/
		tableList[tableCounter]->fields = NULL;
		tableList[tableCounter]->fieldCounter = 0;
		tableList[tableCounter]->elements = 0;
		/*-----------------------*/


		/*Lendo campos => strtok*/
		token = strtok(s[2], ",");
		while (token != NULL) {

			fmd = match(token, "^\\s*(.*)\\s+(.*)\\s*$", 3);

			d = match(fmd[1], "^\\s*(.*)\\s+(.*)\\s*$", 3);
			if(d != NULL){
				fmd[1] = d[1];
				fmd[2] = d[2];
			}
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
		free(token);
		for(i = 0; i < 3; i++) free(s[i]);
		free(s);
		return TRUE;
	}
	return FALSE;

}

/*Função para criar arquivo ordenado de acordo com campo de escolha do usuário (index)*/
BOOLEAN create_index(char *cmd, VARS *global){
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

		global->nindexes++; //---> para statistics

		/*Para ShowAllIndexes*/
		indexList = realloc(indexList, sizeof(INDEX)*(global->nindexes));
		indexList[global->nindexes-1].tableName = (char *) malloc(sizeof(char)*(strlen(s[1])+1));
		indexList[global->nindexes-1].fieldName = (char *) malloc(sizeof(char)*(strlen(s[2])+1));
		strcpy(indexList[global->nindexes-1].tableName, s[1]);
		strcpy(indexList[global->nindexes-1].fieldName, s[2]);
		/*-------------------*/


		/*Copiadno de tmp para dat*/
		tmp = (char*) malloc(sizeof(char)*(strlen(s[1])+5));
		dat = (char*) malloc(sizeof(char)*(strlen(s[1])+5));
		idx = (char*) malloc(sizeof(char)*(strlen(s[1])+6+strlen(s[2])));


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
					fprintf(fp2, "%d %d\n", typeI[i], rows[i]);

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
					fprintf(fp2, "%lf %d\n", typeD[i], rows[i]);

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
					free(p[0]);
					free(p);
				}

				sortCHAR(rows, typeC, tableList[table-1]->elements);
				for(i = 0; i < tableList[table-1]->elements; i++)
					fprintf(fp2, "%s %d\n", typeC[i], rows[i]);

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
BOOLEAN insert(char *cmd, VARS *global) {
	char **s, *aux;
	FILE *fp;
	int i;

	/*Recupera o nome da tabela, os campos e os respectivos valores*/
	s = match(cmd, "^\\s*insert\\s+into\\s+(.*)\\s+\\((.*)\\)\\s+values\\s+\\((.*)\\);$", 4);
	/*-------------------------------------------------------------*/

	if(s != NULL){

		global->ninserts++; //---> para statistics

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

/*Funcao para buscar elementos nos arquivos tmp e idx*/
BOOLEAN selector(char *cmd, VARS *global) {
	char **s, *new;
	char *dat, *tmp, *idx;
	int table, tokenCounter, found = 0;
	FILE *fp = NULL, *fp1 = NULL, *fp2 = NULL;
	s = match(cmd, "^\\s*select\\s+(.*)\\s+(.*)\\s+'(.*)'\\s*;$", 4);
	// s[1] -> tabela
	// s[2] -> campo
	// s[3] -> valor
	if(s != NULL){
		global->recordsInLastBinary = 0;
		global->recordsInLastSequential = 0;
		global->nselects++; // --> para statistics

		tmp = (char*) malloc(sizeof(char)*(strlen(s[1])+5));
		dat = (char*) malloc(sizeof(char)*(strlen(s[1])+5));
		idx = (char*) malloc(sizeof(char)*(strlen(s[1])+6+strlen(s[2])));


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
		fp = fopen(idx, "r");
		fp1 = fopen(tmp, "r");
		fp2 = fopen(dat, "r");
		/*-------------------------*/

		/*Descobrir as posicoes da tabela e do campo que procuramos, respectivamente*/
		for(table = 1; strcmp(tableList[table-1]->tablename, s[1]); table++); // Para quando achar a table de nome s[1]
		for(tokenCounter = 1; strcmp(tableList[table-1]->fields[tokenCounter-1]->fieldname, s[2]) != 0; tokenCounter++); // Para quando achar o campo de nome s[2]
		/*--------------------------------------------------------------------------*/

		/*Chama binsearch somente se existir *.idx e *.dat*/
		if(fp2 != NULL && fp != NULL)
			found += binSearch(fp, fp2, tokenCounter, tableList[table-1]->fields[tokenCounter-1]->fieldtype, s[3], global);
		/*------------------------------------------------*/

		/*Chama seqsearch somente se exstir .tmp*/
		if(fp1 != NULL)
			found += seqSearch(fp1, tokenCounter, tableList[table-1]->fields[tokenCounter-1]->fieldtype, s[3], global);
		/*--------------------------------------*/

		if(found == 0) printf("null\n"); // Found != 0 -> achei pelo menos um


		/*Free*/
		if(fp != NULL)
			fclose(fp);
		if(fp1 != NULL)
			fclose(fp1);
		if(fp2 != NULL)
			fclose(fp2);
		free(tmp);
		free(idx);
		free(dat);

		return TRUE;
	}
	return FALSE;

}

/*Funcao inutil que faz a mesma coisa do create index*/
BOOLEAN sort(char *cmd, VARS *global) {
	char **s, *string;
	int i;
	s = match(cmd, "^\\s*sort\\s+(.*)$", 2);
	//s[1] -> tabela(campo)
	if(s != NULL){
		global->nsorts++; //--> para statistics
		global->nindexes--; //--> para statistics

		/*Criando a string para chamar create index*/
		string = malloc(sizeof(char)*(strlen(s[1])+15));
		strcpy(string, "create index ");
		strcat(string, s[1]);
		/*-----------------------------------------*/

		create_index(string, global); // Finalmente chama create index

		free(string);
		for(i = 0; i < 3; i++) free(s[i]);
		free(s);
		return TRUE;
	}

	return FALSE;
}

/*Função para mostrar todas as tabelas*/
BOOLEAN showalltables(char *cmd, VARS *global) {
	char **s;
	int i, j;
	s = match(cmd, "^showalltables[;]?$", 1);
	if(s != NULL){
		global->nshowalltables++; // --> para statistics
		for(j = 0; j < tableCounter; j++){
			printf("\nTablename: %s\n", tableList[j]->tablename);

			for(i = 0; i < tableList[j]->fieldCounter; i++){
				/*Escolhendo o tipo de dado*/
				switch(tableList[j]->fields[i]->fieldtype){
					case INT:
						printf("\tField: %s Type: %s Size %d\n", tableList[j]->fields[i]->fieldname, "int", tableList[j]->fields[i]->size);
						break;
					case DOUBLE:
						printf("\tField: %s Type: %s Size %d\n", tableList[j]->fields[i]->fieldname, "double", tableList[j]->fields[i]->size);
						break;
					case FLOAT:
						printf("\tField: %s Type: %s Size %d\n", tableList[j]->fields[i]->fieldname, "float", tableList[j]->fields[i]->size);
						break;
					case CHAR:
						printf("\tField: %s Type: %s Size %d\n", tableList[j]->fields[i]->fieldname, "char", tableList[j]->fields[i]->size);
						break;
				}
			}
			printf("\n");
		}
		free(s[0]);
		free(s);
		return TRUE;
	}
	return FALSE;
}

/*Funcao para mostrar indexes*/
BOOLEAN showallindexes(char *cmd, VARS *global) {
	char **s;
	int i;
	s = match(cmd, "^showallindexes[;]?$", 1);
	if(s != NULL){
		global->nshowallindexes++; // --> para statistics
		// deve estar na ordem de criaçao dos ı́ndices
		for (i = 0; i < global->nindexes; i++){
			printf("\nIndex information\n");
			// nome da tabela relacionada ao ı́ndice i
			printf("\tTablename: %s\n", indexList[i].tableName);
			// nome do campo indexado
			 printf("\tFieldname: %s\n\n", indexList[i].fieldName);
			}
		free(s[0]);
		free(s);
		return TRUE;
	}
	return FALSE;
}

/*Funcao que da informacoes acerca dos dados*/
BOOLEAN statistics(char *cmd, VARS global) {
	char **s;
	s = match(cmd, "^statistics[;]?$", 1); // []? significa que pode ou não ter
	if(s != NULL){
		printf("#Tables: %d\n", global.ntables);
		printf("#Indexes: %d\n", global.nindexes);
		printf("#Inserts: %d\n", global.ninserts);
		printf("#Selects: %d\n", global.nselects);
		printf("#Sorts: %d\n", global.nsorts);
		printf("#ShowAllTables: %d\n", global.nshowalltables);
		printf("#ShowAllIndexes: %d\n", global.nshowallindexes);
		printf("#Records in last select (binary search): %d\n", global.recordsInLastBinary);
		printf("#Records in last select (sequential search): %d\n", global.recordsInLastSequential);

		return TRUE;
	}
	return FALSE;
}


void  shell(FILE *stream) {
	char *cmd = NULL;
	int i, j;
	VARS global;

	/*Porque global eh pros fracos*/
	global.nindexes = 0;
	global.ntables = 0;
	global.ninserts = 0;
	global.nselects = 0;
	global.nsorts = 0;
	global.nshowalltables = 0;
   	global.nshowallindexes = 0;
	global.recordsInLastBinary = 0;
   	global.recordsInLastSequential = 0;
	/*E nao da pra settar na struct :(*/


	while (!feof(stream)) {
		if(cmd != NULL)
			free(cmd);
		cmd = readLine(stream);

		if (create_table(cmd, &global)) { continue; }
		if (create_index(cmd, &global)) { continue; }
		if (insert(cmd, &global)) { continue; }
		if (selector(cmd, &global)) { continue; }
		if (sort(cmd, &global)) { continue; }
		if (showalltables(cmd, &global)) { continue; }
		if (showallindexes(cmd, &global)) { continue; }
		if (statistics(cmd, global)) { continue; }
	}

	/*Liberando o resto*/
	for(i = 0; i < tableCounter; i++){ // tables
		free(tableList[i]->tablename);
		for(j = 0; j < tableList[i]->fieldCounter; j++){
			free(tableList[i]->fields[j]->fieldname);
			free(tableList[i]->fields[j]);
		}
		free(tableList[i]->fields);
		free(tableList[i]);
	}
	free(tableList);

	for(i = 0; i < global.nindexes; i++){ // indexList
		free(indexList[i].tableName);
		free(indexList[i].fieldName);
	}
	free(indexList);
	free(cmd);
	/*-----------------*/

}


/*===============MAIN=================*/
int main(int argc, char *argv[]) {
	char *file;
	FILE *fp;

	file = readLine(stdin); // le arquivo com os comandos
	fp = fopen(file, "r");
	free(file);

	shell(fp);

	fclose(fp);

	return 0;
}
