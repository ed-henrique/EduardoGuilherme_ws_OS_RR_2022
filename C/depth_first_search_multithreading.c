#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define MAX 8

pthread_t tid[MAX];
pthread_mutex_t lock;

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
    printf("%ld ", x);
    
    pthread_mutex_lock(&lock);
    visited[x] = 1;
    for (long j = 0; j < MAX; j++) {
        long tmp = visited[j];
        pthread_mutex_unlock(&lock);
        if (A[x][j] == 1 && !tmp) {
            DFS((void*) j);
        }
    }
    
    pthread_exit(NULL);
}

long main() {
    long i = 0;
    long error = 0;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf(">> ERROR MUTEX\n");
        return 1;
    }

    while (i < MAX) {
        error = pthread_create(&tid[i], NULL, DFS, (void*) i);
        if (error != 0) {
            puts(">> ERROR");
            strerror(error);
        }
        i++;
    }

    for (long i = 0; i < MAX; i++) pthread_join(tid[i], NULL);

    printf("\n");
    pthread_exit(NULL);


    return 0;
}