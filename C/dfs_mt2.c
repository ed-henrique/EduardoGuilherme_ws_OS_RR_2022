#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "stack.h"

#define NUM_NODES 3
#define THREAD_COUNT 4

pthread_t tid[THREAD_COUNT];
sem_t mutex, see_mutex;

clock_t start, end;
double cpu_time_used;

long node_operating = 0;
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
        printf("    %2d | ", i);
        for (long j = 0; j < NUM_NODES; j++) printf("%d ", graph[i][j]);
        printf("\n");
    }
}

void DFS(Stack* globalStack) {
    long current = -1;
    while (1) {
        if (current = -1) {
            sem_wait(&mutex);

            if (stackIsEmpty(globalStack)) {
                sem_post(&mutex);
                return;
            }

            current = pop(globalStack);

            sem_wait(&see_mutex);
            printf("%ld ", current);
            sem_post(&see_mutex);

            sem_wait(&see_mutex);
            if (visited[current]) {
                sem_post(&see_mutex);
                sem_post(&mutex);
                continue;
            }

            visited[current] = 1;
            node_operating++;

            sem_post(&see_mutex);
            sem_post(&mutex);
        }

        long index = 0;
        long local[NUM_NODES];
        for (long i = 0; i < NUM_NODES; i++) {
            if (graph[current][i] == 1) {
                sem_wait(&see_mutex);
                if (visited[i]) {
                    sem_post(&see_mutex);
                    continue;
                } else {
                    if (parent[i] < 0) {
                        parent[i] = current;
                        local[index++] = i;
                        //visited[i] = 1;
                    }

                    sem_post(&see_mutex);
                }
            }
        }

        sem_wait(&mutex);

        for (long i = 0; i < index; i++) {
            push(globalStack, local[i]);
        }
        
        if (!stackIsEmpty(globalStack)) {
            current = pop(globalStack);
            //visited[current] = 1;

            sem_wait(&see_mutex);
            printf("%ld ", current);
            sem_post(&see_mutex);

        } else {
            current = -1;
            node_operating--;
        }

        sem_post(&mutex);
    }
}

int main() {
    createGraph();
    printGraph();

    for (long i = 0; i < NUM_NODES; i++) parent[i] = -1;
    
    printf("\nStarting DFS using multithreading...\n\n");

    sem_init(&mutex, 0, 1);
    sem_init(&see_mutex, 0, 1);

    start = clock();
    
    Stack* globalStack = createStack();
    push(globalStack, 0);
    parent[0] = 0;

    printf("    ");
    for (long i = 0; i < THREAD_COUNT; i++) pthread_create(&tid[i], NULL, (void*) DFS, (void*) globalStack);
    for (long i = 0; i < THREAD_COUNT; i++) pthread_join(tid[i], NULL);

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\n\nTime elapsed = %fs\n\n", cpu_time_used);

    destroyStack(&globalStack);
    sem_destroy(&mutex);
    sem_destroy(&see_mutex);
    pthread_exit(NULL);

    return 0;
}