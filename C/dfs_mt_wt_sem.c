#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "stack.h"

#define NUM_NODES 800
#define THREAD_COUNT 4

typedef struct thread {
    long number;
    pthread_t tid;
} Thread;

Thread threads[THREAD_COUNT];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

clock_t start, end;
double cpu_time_used;

char* color;
long parent[NUM_NODES];
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
        printf("\033[35m%6d\033[0m | ", i);
        for (long j = 0; j < NUM_NODES; j++) printf("%d ", graph[i][j]);
        printf("\n");
    }
}

void DFS(Stack* globalStack) {
    long current = -1;
    while (1) {
        if (current = -1) {
            pthread_mutex_lock(&mutex);

            if (stackIsEmpty(globalStack)) {
                pthread_mutex_unlock(&mutex);
                return;
            }

            current = pop(globalStack);

            if (pthread_self() == threads[0].tid) color = "\033[31m";
            else if (pthread_self() == threads[1].tid) color = "\033[32m";
            else if (pthread_self() == threads[2].tid) color = "\033[33m";
            else color = "\033[34m";

            printf("%s%ld ", color, current);

            if (visited[current]) {
                pthread_mutex_unlock(&mutex);
                continue;
            }

            visited[current] = 1;

            pthread_mutex_unlock(&mutex);
        }

        long index = 0;
        long local[NUM_NODES];
        for (long i = 0; i < NUM_NODES; i++) {
            if (graph[current][i] == 1) {
                pthread_mutex_lock(&mutex);
                if (visited[i]) {
                    pthread_mutex_unlock(&mutex);
                    continue;
                } else {
                    if (parent[i] < 0) {
                        parent[i] = current;
                        local[index++] = i;
                    }
                    pthread_mutex_unlock(&mutex);
                }
            }
        }

        pthread_mutex_lock(&mutex);

        for (long i = index - 1; i >= 0; i--) push(globalStack, local[i]);
        
        if (stackIsEmpty(globalStack)) current = -1;

        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    createGraph();
    printGraph();

    for (long i = 0; i < NUM_NODES; i++) parent[i] = -1;
    
    printf("\nStarting DFS using multithreading...\n\n");

    start = clock();
    
    Stack* globalStack = createStack();
    push(globalStack, 0);
    parent[0] = 0;

    for (long i = 0; i < THREAD_COUNT; i++) {
        threads[i].number = i;
        pthread_create(&threads[i].tid, NULL, (void*) DFS, (void*) globalStack);
    }
    for (long i = 0; i < THREAD_COUNT; i++) pthread_join(threads[i].tid, NULL);

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\033[0m\n\nTime elapsed = \033[35m%fs\n\n", cpu_time_used);

    destroyStack(&globalStack);
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);

    return 0;
}