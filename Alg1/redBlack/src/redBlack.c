/*
 * =====================================================================================
 *
 *       Filename:  redBlack.c
 *
 *    Description:  Red Black Tree Implementation
 *
 *        Version:  1.0
 *        Created:  12/07/16 14:39:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ltkills
 *   Organization:  The University of Sao Paulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <redBlack.h>


/*Searches through RedBlack Tree*/
struct node *search(int element, struct node *root) {
	if(root == NULL) return NULL;
	if(root->key > element) return search(element, root->left);
	else if(root->key < element) return search(element, root->right);
	else return root;
}


/*Finds out if now is left or right son*/
int whichSon(struct node *now) {
	if(now->parent == NULL) return -1;
	else if(now == now->parent->left) return LEFT;
	else if(now == now->parent->right) return RIGHT;
}

/*Right rotation for balancing*/
void rotate_right(struct tree *tree, struct node *now) {
	struct node *aux = now->parent, *aux2 = NULL;

	if(now->parent != NULL && whichSon(now) == LEFT) now->parent->left = now->left;
	if(now->parent != NULL && whichSon(now) == RIGHT) now->parent->right = now->left;

	if(now == tree->root) tree->root = now->left;
	now->parent = now->left;

	if(now->left != NULL) now->left->parent = aux;
	if(now->left != NULL && now->left->right != NULL) now->left->right->parent = now;

	aux = now->left;
	if(aux != NULL) aux2 = aux->right;
	aux->right = now;
	now->left = aux2;
	now = aux;

}

/*Left rotation*/
void rotate_left(struct tree *tree, struct node *now) {
	struct node *aux = now->parent, *aux2 = NULL;

	if(now->parent != NULL && whichSon(now) == LEFT) now->parent->left = now->right;
	if(now->parent != NULL && whichSon(now) == RIGHT) now->parent->right = now->right;

	if(now == tree->root) tree->root = now->right;
	now->parent = now->right;

	if(now ->right != NULL) now->right->parent = aux;
	if(now->right != NULL && now->right->left != NULL) now->right->left->parent = now;

	aux = now->right;
	if(aux != NULL) aux2 = aux->left;
	aux->left = now;
	now->right = aux2;
	now = aux;
}

/*Simple binary tree insertion (bigger keys to right)*/
void insertABB(struct node *now, struct node *root) {
	if(root->key == now->key) return;
	if(root->key > now->key) {
		if(root->left != NULL) insertABB(now, root->left);
		else {
			now->parent = root;
			root->left = now;
		}
	} else {
		if(root->right != NULL) insertABB(now, root->right);
		else {
			now->parent = root;
			root->right = now;
		}
	}
}


/*Returns father of father of now*/
struct node *grandpa(struct node *now) {
	if(now->parent == NULL) return NULL;
	return now->parent->parent;
}

/*Returns brother of father of now*/
struct node *uncle(struct node *now) {
	if(now->parent == NULL || grandpa(now) == NULL) return NULL;
	if(whichSon(now->parent) == LEFT) return now->parent->parent->right;
	else if(whichSon(now->parent) == RIGHT) return now->parent->parent->left;
}

void case1(struct tree *tree, struct node *now);

/*Non-crossed sons (cis)*/
void case5(struct tree *tree, struct node *now) {
	struct node *granpa = grandpa(now);
	now->parent->color = BLACK;
	granpa->color = RED;
	if(whichSon(now) == LEFT) rotate_right(tree, granpa);
	else rotate_left(tree, granpa);
}

/*Crossed Sons (trans)*/
void case4(struct tree *tree, struct node *now) {
	if(whichSon(now) == RIGHT && whichSon(now->parent) == LEFT) {
		rotate_left(tree, now->parent);
		now = now->left;
	} else if(whichSon(now) == LEFT && whichSon(now->parent) == RIGHT) {
		rotate_right(tree, now->parent);
		now = now->right;
	}
	case5(tree, now);
}

/*Father and uncle are red*/
void case3(struct tree *tree, struct node *now) {
	struct node *u = uncle(now), *granpa = grandpa(now);
	if((u != NULL) && (u->color == RED)) {
		now->parent->color = BLACK;
		u->color = BLACK;
		granpa->color = RED;
		case1(tree, granpa);
	}
	else case4(tree, now);
}

/*Father is black*/
void case2(struct tree *tree, struct node *now) {
	if(now->parent->color == BLACK) return; // goooood
	else case3(tree, now);
}

/*Insertion at the root*/
void case1(struct tree *tree, struct node *now) {
	if(now->parent == NULL) now->color = BLACK;
	else case2(tree, now);
}

/*Balanced insertion*/
void insert(struct tree *tree, int element) {
	// Prepare node (YOUUU ARE NOT PREPAAAAARED)
	if(search(element, tree->root) != NULL) return; // Already-inserted node
	struct node *now = calloc(1, sizeof(struct node));
	now->key = element;
	now->color = RED;

	// Empty tree
	if(tree->size == 0) {
		now->color = BLACK;
	   	tree->root = now;
		return;
	}

	insertABB(now, tree->root); // inserts as in an binary tree
	case1(tree, now);
}

/*=========================TOYS===============================*/

int smallest(struct node *root) {
	if(root == NULL) return INT_MIN;
	else if(root->left != NULL) return smallest(root->left);
	else return root->key;
}

int biggest(struct node *root) {
	if(root == NULL) return INT_MIN;
	else if(root->right != NULL) return biggest(root->right);
	else return root->key;
}

/*Successor of element*/
int after(struct tree *tree, int element) { // smallest node of right subtree or first right dad
	struct node *now = search(element, tree->root);
	int ans;

	if(now == NULL) return INT_MIN;
	ans = smallest(now->right);

	if(ans == INT_MIN) { // go up (till first right dad's son)
		while(whichSon(now) == RIGHT) now = now->parent;
		if(whichSon(now) == -1) return INT_MIN;
		ans = now->parent->key;
	}
	return ans;
}

/*Predecessor of element*/
int before(struct tree *tree, int element) { // biggest node of left subtree or first left dad
	struct node *now = search(element, tree->root);
	int ans;

	if(now == NULL) return INT_MIN;
	ans = biggest(now->left);

	if(ans == INT_MIN) { // go up (till first left dad's son)
		while(whichSon(now) == LEFT) now = now->parent;
		if(whichSon(now) == -1) return INT_MIN;
		ans = now->parent->key;
	}
	return ans;
}

/*Maximum value on entire tree*/
int max(struct tree *tree, struct node *root) {
	int maximum = INT_MIN;

	if(tree->size == 0) return INT_MIN;

	if(root->key > maximum) maximum = root->key;
	if(root->left != NULL && maximum < max(tree, root->left)) maximum = max(tree, root->left);
	if(root->right != NULL && maximum < max(tree, root->right)) maximum = max(tree, root->right);

	return maximum;
}

/*Minimum value on entire tree*/
int min(struct tree *tree, struct node *root) {
	int minimum = INT_MAX;

	if(tree->size == 0) return INT_MAX;

	if(root->key < minimum) minimum = root->key;
	if(root->left != NULL && minimum > min(tree, root->left)) minimum = min(tree, root->left);
	if(root->right != NULL && minimum > min(tree, root->right)) minimum = min(tree, root->right);

	return minimum;
}
/*========================PRINTING=============================*/
void preOrder(struct node *root) {
	if(root == NULL) return;
	printf("%d ", root->key);
	preOrder(root->left);
	preOrder(root->right);
}

void inOrder(struct node *root) {
	if(root == NULL) return;
	inOrder(root->left);
	printf("%d ", root->key);
	inOrder(root->right);
}

void postOrder(struct node *root) {
	if(root == NULL) return;
	postOrder(root->left);
	postOrder(root->right);
	printf("%d ", root->key);
}
/*================Constructors and Destructors=================*/

/*Returns empty tree*/
struct tree *buildTree(void) {
	struct tree *tree = calloc(1, sizeof(struct tree));
	return tree;
}


/*Destroys tree recursivelly*/
void destroyTree(struct node *root) {
	if(root->left != NULL) destroyTree(root->left);
	if(root->right != NULL) destroyTree(root->right);
	free(root);
}
/*=============================================================*/
