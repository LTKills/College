#ifndef _REDBLACK_H_
#define _REDBLACK_H_


struct node {
	struct node *left, *right, *parent;
	int key;
	int color;
};

struct tree {
	struct node *root;
	int size;
};

enum color{
	RED,
	BLACK
};

enum side{
	LEFT,
	RIGHT
};

// What really matters...
void insert(struct tree *tree, int element);
void insertABB(struct node *now, struct node *root);

// Toys
int after(struct tree *tree, int element);
int before(struct tree *tree, int element);
int max(struct tree *tree, struct node *root);
int min(struct tree *tree, struct node *root);
void preOrder(struct node *root);
void inOrder(struct node *root);
void postOrder(struct node *root);

// Constructors
struct tree *buildTree(void);
void destroyTree(struct node *root);

#endif
