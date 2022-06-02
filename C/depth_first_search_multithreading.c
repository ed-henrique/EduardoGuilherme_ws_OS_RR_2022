#include <stdio.h>
#include <pthread.h>
#include "stack.h"

#define MAX 8

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

long visited[MAX] = {0};
long A[MAX][MAX] = {
    {0,1,1,1,0,0,0,0},
    {1,0,1,0,0,0,0,0},
    {1,1,0,1,1,0,0,0},
    {1,0,1,0,1,0,0,0},
    {0,0,1,1,0,1,1,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,1},
    {0,0,0,0,0,0,1,0}
};

void* DFS(void* i) {
    long x = (long) i;
    Stack* s = createStack(MAX * 2);

    push(s, x);

    while (!stackIsEmpty(s)) {
        long y = pop(s);

        pthread_mutex_lock(&lock);
        
        if (!visited[y]) {
            printf("%ld ", y);
            visited[y] = 1;
        }

        pthread_mutex_unlock(&lock);

        for (long j = 0; j < MAX; j++) {
            if (A[y][j] == 1 && !visited[j]) {
                push(s, j);
            }
        }
    }

    destroyStack(&s);
}

long main() {
    pthread_t tid[MAX];

    for (long i = 0; i < MAX; i++) pthread_create(&tid[i], NULL, DFS, (void*) i);
    for (long i = 0; i < MAX; i++) pthread_join(tid[i], NULL);

    printf("\n");

    pthread_exit(NULL);

    return 0;
}