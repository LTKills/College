#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


int finished(int *distance, int vertexes) {
    int i, counter = 0;
    for(i = 0; i < vertexes; i++)
        if(distance[i] != -1) counter++;
    if(counter > 1) return 0;
    return 1;
}

void updateDistance(int **graph, int *distance, int *prev, int vertexes, int aux) {
    int i = 0;
    for(i = 0; i < vertexes; i++) {
        if(distance[i] != -1 && graph[aux][i] != 0 &&
                graph[aux][i] < distance[i]) {
            distance[i] = graph[aux][i];
            prev[i] = aux;
        }
    }
}


int getMinDistance(int *distance, int vertexes) {
    int aux = -1, min = INT_MAX, i;

    for(i = 0; i < vertexes; i++) {
        if(distance[i] != -1 && min > distance[i]) {
            min = distance[i];
            aux = i;
        }
    }

    return aux;
}



void prim(int **graph, int *distance, int vertexes) {
    int aux = 0, i;
    int *prev = malloc(sizeof(int)*vertexes);

    while(!finished(distance, vertexes)) {
        updateDistance(graph, distance, prev, vertexes, aux);

        distance[aux] = -1; // visit aux

        aux = getMinDistance(distance, vertexes);
        if(prev[aux] < aux)
            printf("(%d,%d) ", prev[aux], aux);
        else
            printf("(%d,%d) ", aux, prev[aux]);
    }

    free(prev);
    printf("\n");

}

int main(int argc, char *argv[]) {
    int **graph = NULL, *distance = NULL;
    int i, src, dest, weight;
    int vertexes, edges;

    scanf("%d %d", &vertexes, &edges);

    /*Creating vectors*/
    graph = malloc(sizeof(int*)*vertexes);
    for(i = 0; i < vertexes; i++) graph[i] = calloc(vertexes, sizeof(int));

    distance = calloc(vertexes, sizeof(int));
    for(i = 1; i < vertexes; i++) distance[i] = INT_MAX;


    /*Setting up graph*/
    for(i = 0; i < edges; i++) {
        scanf("%d %d %d", &src, &dest, &weight);
        graph[src][dest] = weight;
        graph[dest][src] = weight;
    }


    /*prim's algorithm*/
    prim(graph, distance, vertexes);


    /*Deallocating*/
    for(i = 0; i < vertexes; i++) free(graph[i]);
    free(graph);
    free(distance);

    return 0;
}
