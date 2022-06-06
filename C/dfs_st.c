#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "stack.h"

#define NUM_NODES 50

clock_t start, end;
double cpu_time_used;

long visited[NUM_NODES] = {0};
long graph[NUM_NODES][NUM_NODES];

void createGraph() {
    srand(time(NULL));

    printf("\nGraph is being created... ");

    for(int i = 0; i < NUM_NODES; i++) {
        for(int j = 0; j < NUM_NODES; j++) {
            if (i != j) {
                graph[i][j] = rand() % 2;
                graph[j][i] = graph[i][j];
            } else {
                graph[i][j] = 0;
            }
        }
    }

    printf("DONE!\n\n");
    printf("GRAPH:\n\n");
}

void printGraph() {
    for (long i = 0; i < NUM_NODES; i++) {
        printf("    %2d | ", i);
        for (long j = 0; j < NUM_NODES; j++) printf("%d ", graph[i][j]);
        printf("\n");
    }
}

void* DFS(void* i) {
    long x = (long) i;
    Stack* s = createStack();

    push(s, x);

    while (!stackIsEmpty(s)) {
        long y = pop(s);

        if (!visited[y]) {
            printf("%ld ", y);
            visited[y] = 1;
        }

        for (long j = 0; j < NUM_NODES; j++) {
            if (graph[y][j] == 1 && !visited[j]) {
                push(s, j);
            }
        }
    }

    destroyStack(&s);
}

long main() {
    createGraph();
    printGraph();

    printf("Starting DFS with singlethread...\n\n    ");
    
    start = clock();

    DFS((void*) 0);

    end = clock();

    printf("\n\nProgram is over.\n\n");

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time elapsed = %fs\n\n", cpu_time_used);

    return 0;
}