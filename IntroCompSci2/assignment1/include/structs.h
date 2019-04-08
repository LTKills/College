#ifndef _STRUCTS_H_
#define _STRUCTS_H_

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

/*Variaveis para statistics*/
typedef struct{
	int ntables, ninserts, nindexes, nselects, nsorts, nshowalltables, nshowallindexes,
	recordsInLastBinary, recordsInLastSequential;
} VARS;
/*-------------------------*/


#endif
