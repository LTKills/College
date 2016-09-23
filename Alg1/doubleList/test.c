#include <stdlib.h>
#include <stdio.h>
#include <dlist.h>


int main(int argc, char *argv[]){
	int sizes, i, n;
	dcontroler_t control = create_dList();

	if(is_dEmpty(control) == TRUE) printf("Empty\n");
	else printf("Not empty\n");

	scanf("%d", &sizes);

	for(i = 0; i < sizes; i++){
		scanf("%d", &n);
		insert_dEnd(&control, n);
		printf("%d ", control.element);
	}
		printf("\n");

	if(is_dEmpty(control) == TRUE) printf("Empty\n");
	else printf("Not empty\n");

	printDat_dList(control);
	printf("\n");

	control = exterminate_dList(control);
	printDat_dList(control);
	return 0;
}
