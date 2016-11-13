/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  AVL tree implementation
 *
 *        Version:  1.0
 *        Created:  11/12/16 23:48:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  The University of Sao Paulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <avl.h>

enum {
	PROGNAME,
	ELEMENTS,
	OPERATIONS,
	NARGS
};

int main(int argc, char *argv[]) {
	int i, key, op;
	struct NODE *root = malloc(sizeof(struct NODE));
	struct NODE *yay;


	if(argc != NARGS) {
		printf("usage %s elements operations\n", argv[PROGNAME]);
		return -1;
	}

	scanf("%d", &key);
	root->key = key;
	root->left = NULL;
	root->right = NULL;

	for(i = 1; i < atoi(argv[ELEMENTS]); i++) {
		scanf("%d", &key);
		insertTree(root, key);
	}

	for(i = 0; i < atoi(argv[OPERATIONS]); i++) {
		printf("1.Insert\t2.Remove\t3.Print\t\t4.Search\n");
		scanf("%d", &op);
		switch(op) {

			case 1:
				printf("Key: ");
				scanf("%d", &key);
				printf("\n");
				insertTree(root, key);
				break;

			case 2:
				printf("Key: ");
				scanf("%d", &key);
				printf("\n");
				removeTree(root, key);
				break;

			case 3:
				printTree(root);
				break;

			case 4:
				printf("Key: ");
				scanf("%d", &key);
				printf("\n");
				yay = searchTree(root, key);
				printf("%p\t%d\n", yay, yay->key);
				break;
		}
	}

	destroyTree(root);
	return 0;
}


