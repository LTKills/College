#include <stdlib.h>
#include <stdio.h>
#include <list.h>


int main(int argc, char *argv[]){
	int sizes, i, n;
	controler_t control = createList();

	if(isEmpty(control) == TRUE) printf("Empty\n");
	else printf("Not empty\n");

	scanf("%d", &sizes);

	for(i = 0; i < sizes; i++){
		scanf("%d", &n);
		insertStart(&control, n);
		printf("%d ", control.element);
	}
		printf("\n");

	if(isEmpty(control) == TRUE) printf("Empty\n");
	else printf("Not empty\n");

	printDatList(control);
	printf("\n");

	control = exterminateList(control);
	printDatList(control);
	return 0;
}
