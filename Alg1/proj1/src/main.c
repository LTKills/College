/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Simple treating of inputs and outputs
 *
 *        Version:  1.0
 *        Created:  10/09/2016 11:34:14 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  The University of Sao Paulo
 *
 * =====================================================================================
 */


// Coding is also art
#include <stdlib.h>
#include <stdio.h>
#include <file.h>
#include <list.h>


typedef enum{
	INSERT,
	RM,
	SEARCH
} OP;

typedef enum{
	LINKED,
	SKIP
} LIST;

int main(int argc, char *argv[]){
	controler_t myControl = createList();
	list_t *search;
	int op, list, n, i;
	char *address = NULL, *ip = NULL;

	scanf("%d", &n);

	for(i = 0; i < n; i++){
		/*Reading inputs*/
		scanf("%d %d ", &op, &list);

		switch(list){

			case LINKED:
				switch(op){
					case INSERT:
						address = readLine(stdin, SPACE);
						ip = readLine(stdin, ENTER);
						insertStart(&myControl, address, ip);
						break;
					case RM:
						address = readLine(stdin, ENTER);
						seekAndDestroy(&myControl, address);
						break;
					case SEARCH:
						address = readLine(stdin, ENTER);
						search = searchElement(myControl, address);
						if(search == NULL) printf("-1\n");
						else printf("%s\n", search->ip);
						break;
				}
				break;

			case SKIP:
				switch(op){
					case INSERT:
						address = readLine(stdin, SPACE);
						ip = readLine(stdin, ENTER);
						break;
					case RM:
						address = readLine(stdin, ENTER);
						break;
					case SEARCH:
						address = readLine(stdin, ENTER);
						break;
				}
				break;
		}
	}
	if(myControl.element != 0) exterminateList(&myControl);
	return 0;
}

