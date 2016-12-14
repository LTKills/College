/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Main file for inputs and outputs
 *
 *        Version:  1.0
 *        Created:  12/04/16 14:07:54
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
#include <limits.h>
#include <redBlack.h>

enum {
	ZERO, // worthless
	// worthfull...
	INSERT,
	SUCCESSOR,
	PREDECESSOR,
	MAX,
	MIN,
	PREORDER,
	INORDER,
	POSTORDER,
};

int main(int argc, const char *argv[]) {
	int n, op, i, element, maximum, minimum, aux = INT_MIN;
	struct tree *tree = buildTree(); // Initialize tree

	scanf("%d", &n); // number of operations

	for(i = 0; i < n; i++) {
		scanf("%d", &op);
		switch(op) {
			case INSERT:
				scanf("%d", &element);
				insert(tree, element);
				tree->size++;
				break;

			case SUCCESSOR:
				scanf("%d", &element);
				aux = after(tree, element);
				if(aux == INT_MIN) printf("erro\n");
				else printf("%d\n", aux);
				break;

			case PREDECESSOR:
				scanf("%d", &element);
				aux = before(tree, element);
				if(aux == INT_MIN) printf("erro\n");
				else printf("%d\n", aux);
				break;

			case MAX:
				maximum = max(tree, tree->root);
				if(maximum == INT_MIN) printf("erro\n");
				else printf("%d\n", maximum);
				break;

			case MIN:
				minimum = min(tree, tree->root);
				if(minimum == INT_MAX) printf("erro\n");
				else printf("%d\n", minimum);
				break;

			case PREORDER:
				preOrder(tree->root);
				printf("\n");
				break;

			case INORDER:
				inOrder(tree->root);
				printf("\n");
				break;

			case POSTORDER:
				postOrder(tree->root);
				printf("\n");
				break;

			default:
				printf("Invalid option\n");
				return -1;
				break;
		}
	}

	destroyTree(tree->root); // unbuilds (lol) tree
	free(tree);
	return 0;
}

