#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "stack.h"

#define NUM_NODES 50
#define THREAD_COUNT 4

pthread_t tid[THREAD_COUNT];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

clock_t start, end;
double cpu_time_used;

int finished = 0;
long visited_nodes_counter = 0;
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

//void* DFSearchNode(Stack* localStack, long k) {
void* DFSearchNode(Stack* globalStack, Stack* localStack, long k) {
    push(localStack, k);

    while (!stackIsEmpty(localStack)) {
        long s = pop(localStack);

        if (!visited[s]) {
            visited[s] = 1;
            visited_nodes_counter++;
            
            printf("%ld ", s);

            int localOrGlobal = 1; // 1 for local, 0 for global
            for (long i = NUM_NODES; i >= 0; i--) {
                if (i != s) {
                    if (graph[s][i] == 1 && !localOrGlobal && !visited[s]) {
                        push(globalStack, i);
                    }
                    if (graph[s][i] == 1 && localOrGlobal && !visited[s]) {
                        push(localStack, i);
                        localOrGlobal = 0;
                    }
                }
            }
            
        }
    }
    
}

void DFSearch(void* globalStack) {
    printStack(globalStack);
    Stack* localStack = createStack();
    while (!finished) {
        long k;

        k = pop(globalStack);

        while (visited[k]) {
            if (stackIsEmpty(globalStack)) {
                finished = 1;
                return;
            } else {
                k = pop(globalStack);
            }
        }

        DFSearchNode(globalStack, localStack, k);
        //DFSearchNode(localStack, k);
        //yield()
        if (stackIsEmpty(globalStack)) finished = 1;
        if (finished && visited_nodes_counter < NUM_NODES) {
            finished = 0;
            for (long i = 0; i < NUM_NODES; i++) {
                if (!visited[i]) {
                    push(globalStack, i);
                }
            }
        }
    }
    
}

int main() {
    createGraph();
    printGraph();

    printf("\nStarting DFS using multithreading...\n\n");

    start = clock();
    
    Stack* globalStack = createStack();
    push(globalStack, NUM_NODES - 1);

    for (long i = 0; i < THREAD_COUNT; i++) pthread_create(&tid[i], NULL, (void*) DFSearch, (void*) globalStack);
    for (long i = 0; i < THREAD_COUNT; i++) pthread_join(tid[i], NULL);
    
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\n\nTime elapsed = %f\n\n", cpu_time_used);

    pthread_mutex_destroy(&lock);
    pthread_exit(NULL);

    return 0;
}