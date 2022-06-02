#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* createStack(long capacity) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->height = -1;
    s->capacity = capacity;
    s->data = (long*)calloc(capacity, sizeof(long));
}

void destroyStack(Stack** s_ref) {
    Stack* s = *s_ref;
    free(s->data);
    free(s);
    s_ref = NULL;
}

int stackIsEmpty(Stack* s) {
    return s->height == -1;
}

void printStack(Stack* s) {
    for (long i = 0; i < s->height - 1; i++) {
        printf("%d | ", s->data[i]);
    }
    printf("%d\n", s->data[s->height - 1]);
}

void push(Stack* s, long element) {
    if (s->height == s->capacity - 1) printf("Stack is full!\n");
    else s->data[++s->height] = element;
}

long pop(Stack* s) {
    if (stackIsEmpty(s)) printf("Stack is empty!\n");
    else return s->data[s->height--];
}