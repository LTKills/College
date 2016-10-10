/*
 * =====================================================================================
 *
 *       Filename:  bin3.c
 *
 *    Description:  Binary Tree Implementation
 *
 *        Version:  1.0
 *        Created:  09/29/16 17:01:46
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
#include <bin3.h>


/*Insert a node in the binary tree*/
void insertBin3(NODE *start, NODE *insert){
	if(start->val == insert->val) return;		//	don't want anyone equal here

	if(start->val > insert->val){
		if(start->left == NULL){
			insert->top = start;
			start->left = insert;
			insert->left = NULL;
			insert->right = NULL;
			return;
		}
	   	insertBin3(start->left, insert);
	}

	else if(start->val < insert->val){
		if(start->right == NULL){

			insert->top = start;
			start->right = insert;
			insert->left = NULL;
			insert->right = NULL;
			return;

		}
		insertBin3(start->right, insert);
	}
}

NODE *searchBin3(NODE *start, int value){
	if(start == NULL) return NULL;
	if(start->val == value) return start;
	else if(value > start->val) return searchBin3(start->right, value);
	else return searchBin3(start->left, value);
}

void removeBin3(NODE *start, int value){
	NODE *rm = searchBin3(start, value);

}

printBin3(){


}
