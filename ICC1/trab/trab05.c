/*
 * =====================================================================================
 *
 *       Filename:  trab05.c
 *
 *    Description:  Trabalho 5 - Deque
 *
 *        Version:  1.0
 *        Created:  06/30/16 09:51:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  USP
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ENTER 10
#define STRINGS 2
#define LASTWORD 1


/*Função para ler strings alocando na heap*/
char *readLine(FILE *fp, int *counter){
	int i = 0;
	char *string = NULL, c;

	do{
		c = fgetc(fp);
		string = (char *) realloc(string, sizeof(char)*(i+1));
		string[i++] = c;
	}while(c != ENTER);
	string[i-1] = '\0';

	*counter = i-1;
	return string;
}

typedef struct Node Node;
typedef struct Deque Deque;

/* Estrutura que armazena um elemento do Deque. */
struct Node{

	Node *previous;
	char name;
	Node *next;

};

/* Estrutura que armazena o Deque completo (referência para os Nodes encadeados). */
struct Deque{

	Node *first;
	Node *last;

};

/* Insere um elemento na frente (na cabeça) do Deque. */
void push_front(Deque *deck, char element){
	Node *new;

	new = (Node *) malloc(sizeof(Node));		//	aloca para o novo elemento

	new->name = element;							// 	insere o caracter
	new->next = NULL;
	new->previous = deck->last;					//	atualiza a cabeça
	if(deck->last != NULL)
		deck->last->next = new;
	deck->last = new;
}

/* Insere um elemento atrás (na cauda) do Deque. */
void push_back(Deque *deck, char element){					//	análoga à push_front
	Node *new;

	new = (Node *) malloc(sizeof(Node));

	new->name = element;
	new->previous = NULL;
	new->next = deck->first;
	if(deck->first != NULL)
		deck->first->previous = new;
	deck->first = new;
}


/* Retorna o elemento armazenado na frente do Deque. */
char front(Deque *deck){
	return deck->last->name;
}

/* Retorna o elemento armazenado atrás do Deque. */
char back(Deque *deck){
	return deck->first->name;
}

/* Retorna a quantidade de elementos do Deque. */
int size(Deque *deck){
	int n = 1;
	Node *now = deck->first;

	while(now != deck->last){
		n++;
		now = now->next;
	}
	return n;
}

/* Retorna 1 caso o Deque esteja vazio e 0 caso contrário. */
int empty(Deque *deck){
	if(deck->first == NULL && deck->last == NULL)
		return 1;
	return 0;
}

/* Remove o elemento da frente do Deque. */
void pop_front(Deque *deck){
	Node *now;

	now = deck->last;					//	guarda o último
	deck->last = deck->last->previous;	//	atualiza o vetor de Nodes
	deck->last->next = NULL;

	free(now);

}

/* Remove o elemento de trás do Deque. */
void pop_back(Deque *deck){				//	mesmo esquema do pop front
	Node *now;

	now = deck->first;
	deck->first = deck->first->next;
	deck->first->previous = NULL;

	free(now);
}
/* Aloca um Deque vazio na Heap. */
Deque *create(){
	Deque *deck;
	deck = (Deque *) malloc(sizeof(Deque));

	deck->first = NULL;
	deck->last = NULL;

	return deck;
}

/* Remove todos os elementos do Deque. */
void clear(Deque *deck){
	Node *now;

	now = deck->first;			 // pega o primeiro nó

	while(now->next != NULL){
		now = now->next;
		pop_back(deck);
	}
	free(now);

	deck->last = NULL;				//	mostrar que deck está vazio
	deck->first = NULL;
}

/* Remove todos os elementos e desaloca o Deque. */
void destroy(Deque *deck){
	clear(deck);
	free(deck);
}



/*Print recursivo*/
void printRec(Node *node){
	printf("%c", node->name);
	if(node->next != NULL)
		printRec(node->next);
}

/* Imprime todos os elementos armazenados no Deque. */
void print(Deque *deck){
	printRec(deck->first);
	printf("\n");
}

/*Checa se a resposta é válida*/
int backtracking(char *string, Deque *try, Deque *build, int size, int k){
	Node *buildN = build->first, *tryN = try->first, *lurker = tryN;
	int i, j, counter = 0, answer = 0;
	//printf("K: %d\n", k);
	if(size == k)
		return size;


	/*
	  tryN -> pointer 2
	  lurker -> pointer 1
	  buildN -> contador para o deqque sendo construído
	*/
	//printf("Verificando match\n");
	for(i = 0; i <= size-k; i++){		//	Two pointers
		buildN = build->first;		//	volta o build pro começo
		tryN = lurker;					//	volta o segundo pointer
		for(j = 0; j < k; j++){
			if(tryN->name == buildN->name){
				tryN = tryN->next;			//	avança o segundo pointer
				buildN = buildN->next;			//	avança build
				counter++;
			}else{
				counter = 0;
				break;
			}
		}
		if(counter == k) break;
		lurker = lurker->next;		//	avança o primeiro pointer
	}



	if(counter == k){ 		//	uhuuu match
		push_front(build, string[k]);
		answer += backtracking(string, try, build, size, k+1);
		if(answer == size) return size;
		pop_front(build);
		push_back(build, string[k]);
		answer += backtracking(string, try, build, size, k+1);
		pop_back(build);
		if(answer == size) return size;
	}
	return 0;
}

//========================MAIN==============================
int main(int argc, char *argv[]){
	int opt, size, i, k;
	char *string, *ans;
	Deque *deck, *deck1;
	scanf("%d", &opt);
	switch(opt){
//==========================================================
		case LASTWORD:
			fgetc(stdin);
			string = readLine(stdin, &size);
			deck = create();

			push_back(deck, string[0]);
			deck->last = deck->first;			//	quando o deque possui apenas um elemento, first e last apontam para o mesmo cara

			for(i = 1; i < size; i++){
				if(string[i] >= deck->first->name)	//	escolhe o melhor (começo ou fim)
					push_back(deck, string[i]);
				else
					push_front(deck, string[i]);
			}

			print(deck);

			free(string);
			destroy(deck);
			break;
//==========================================================
		case STRINGS:
			fgetc(stdin);
			string = readLine(stdin, &size);
			ans = readLine(stdin, &size);
			deck = create();
			deck1 = create();

			push_back(deck, ans[0]);
			deck->last = deck->first;

			push_back(deck1, string[0]);
			deck1->last = deck1->first;

			for(i = 1; i < size; i++){
				push_front(deck, ans[i]);
			}

			k = backtracking(string, deck, deck1, size, 1);
			if(k == size)
				printf("S\n");
			else printf("N\n");


			free(string);
			free(ans);
			destroy(deck);
			destroy(deck1);
			break;
	}
	return 0;
}

