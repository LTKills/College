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

void insertBin3(NODE *start, NODE *insert){
	if(start->left->val > insert->val) insertBin3(start->left, insert);
	if(start->right->val < insert->val) insertBin3(start->right, insert);
	else {
		insert->left = start->left;
		start->left = insert;
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
