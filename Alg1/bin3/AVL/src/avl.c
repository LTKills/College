/*
 * =====================================================================================
 *
 *       Filename:  bin.c
 *
 *    Description:  Binary tree functions implementation
 *
 *        Version:  1.0
 *        Created:  11/11/16 17:35:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  The University of Sao Pulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <avl.h>


/*Frees and removes all the tree recursively*/
void destroyTree(struct NODE *root) {
	if(root->left != NULL) destroyTree(root->left);
	if(root->right != NULL) destroyTree(root->right);
	free(root);
}

/*Prints all tree cutelly*/
void printTree(struct NODE *root) {
	printf("%d\n", root->key);
	if(root->left != NULL) printTree(root->left);
	if(root->right != NULL) printTree(root->right);
}

/*Doing rotations*/
void rotate(struct NODE *root) {
	struct NODE *aux;
	if(root->balance > 0) { // rotate left
		aux = root;
	} else {				//	rotate right

	}
}

/*Insert element*/
void insertTree(struct NODE *root, int key) {
	if(root->key == key) return; // no repeated elements allowed
	else if(root->key > key) { // insert left
		root->balance++;
		if(root->left == NULL) {
			root->left = malloc(sizeof(struct NODE));
			root->left->key = key;
			root->left->left = NULL;
			root->left->right = NULL;
			return;
		}
		if(root->balance >= 2) rotate(root);
		return insertTree(root->left, key);
	}
	else {					//	insert right
		root->balance--;
		if(root->right == NULL) {
			root->right = malloc(sizeof(struct NODE));
			root->right->key = key;
			root->right->left = NULL;
			root->right->right = NULL;
			return;
		}
		if(root->balance <= -2) rotate(root);
		return insertTree(root->right, key);
	}
}

/*Search element*/
struct NODE *searchTree(struct NODE *root, int key) {
	struct NODE *aux = root;
	while(aux != NULL) {
		if(aux->key == key) break;
		else if(aux->key > key) aux = aux->left; // biggers to the right
		else if(aux->key < key) aux = aux->right; // smallers to the left
	}
	return aux;
}


/*Remove element*/
void removeTree(struct NODE *root, int key) {
	struct NODE *seek = searchTree(root, key), *aux;
	printf("found %d\n", seek->key);

	if(seek->left == NULL) {
		aux = seek;
		seek = seek->right;
		free(aux);
	} else if(seek->right == NULL) {
		printf("Right null\n");
		aux = seek;
		seek = seek->left;
		free(aux);
	} else {
		for(aux = seek->left; aux->right != NULL; aux = aux->right); // going to the biggest element on the left subtree
		seek->key = aux->key;
		seek->left = aux->left;
		removeTree(aux, aux->key);
	}
}


