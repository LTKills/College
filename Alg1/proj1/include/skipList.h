#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

typedef struct skip_t skip_t;



struct skip_t{
	skip_t *next, *prev, *down, *up;
	char *addres;
	char *ip;
	int isEnd;
};

typedef struct{

} scontroler_t;



#endif
