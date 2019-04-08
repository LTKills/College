#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void updateDistance(int **graph, int *distance, int *prev, int *visited, int vertexes, int aux) {
    int i = 0;
    for(i = 0; i < vertexes; i++) {
        if(!visited[i] && graph[aux][i] != 0 && distance[aux] != INT_MAX &&
                (graph[aux][i] + distance[aux]) < distance[i]) {
					
            distance[i] = graph[aux][i] + distance[aux];
            prev[i] = aux;
        }
    }
}


int getMinDistance(int *distance, int *visited, int vertexes) {
    int aux = -1, min = INT_MAX, i;

    for(i = 0; i < vertexes; i++) {
        if(!visited[i] && min > distance[i]) {
				
            min = distance[i];
            aux = i;
        }
    }

    return aux;
}

// Finds shortest beginning in start and finishing in end
void dijkstra(int **graph, int vertexes, int start, int end) {
    int i, j = -1, aux = 0;
    
    /*Set vectors*/
    int *visited = calloc(vertexes, sizeof(int));
    int *ans = malloc(sizeof(int)*vertexes);
    
    int *distance = malloc(vertexes *sizeof(int));
    for(i = 0; i < vertexes; i++) distance[i] = INT_MAX;
    
    int *prev = malloc(sizeof(int)*vertexes);
    for(i = 0; i < vertexes; i++) prev[i] = -1;
	/*-------------*/
	
	distance[start] = 0;
	aux = start;
	
	for(i = 0; i < vertexes-1; i++) {
		aux = getMinDistance(distance, visited, vertexes);
//		printf("Try: %d vertexes: %d\n", aux, vertexes);
		if(aux != -1) {
			visited[aux] = 1; // visit aux
			updateDistance(graph, distance, prev, visited, vertexes, aux);
		}
	}
	
	
	aux = end;
	while(aux != -1 && prev[aux] != -1) {
		ans[++j] = aux;
		aux = prev[aux];
	}
	if(aux != -1 && aux != end)
		ans[++j] = aux;
    

    while(j >= 0) {
		printf("%d ", ans[j]);
		j--;
	}  

    free(prev);
    free(ans);
    free(visited);
    free(distance);
    printf("\n");

}



int main(int argc, char *argv[]) {
    int **graph = NULL, *distance = NULL;
    int i, src, dest, weight;
    int vertexes, edges, start, end;

    scanf("%d %d", &vertexes, &edges);

    /*Creating vectors*/
    graph = malloc(sizeof(int*)*vertexes);
    for(i = 0; i < vertexes; i++) graph[i] = calloc(vertexes, sizeof(int));


    /*Setting up graph*/
    for(i = 0; i < edges; i++) {
        scanf("%d %d %d", &src, &dest, &weight);
        graph[src][dest] = weight;
    }
 
	/*Minimun path*/
	while(!feof(stdin)) {
		scanf("%d %d", &start, &end);
		if(feof(stdin)) break;
		dijkstra(graph, vertexes, start, end);
	}
	


    /*Deallocating*/
    for(i = 0; i < vertexes; i++) free(graph[i]);
    free(graph);
    free(distance);

    return 0;
}
