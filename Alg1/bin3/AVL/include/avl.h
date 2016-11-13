#ifndef _AVL_H_
#define _AVL_H_

struct NODE {
	int key, balance;
	struct NODE *left, *right;
};


void destroyTree(struct NODE *root);
void printTree(struct NODE *root);
void insertTree(struct NODE *root, int key);
struct NODE *searchTree(struct NODE *root, int key);
void removeTree(struct NODE *root, int key);

#endif
