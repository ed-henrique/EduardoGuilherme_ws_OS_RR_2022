#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* createStack(int capacity) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->height = 0;
    s->capacity = capacity;
    s->data = (int*)calloc(capacity, sizeof(int));
}

void printStack(Stack* s) {
    for (int i = 0; i < s->height - 1; i++) {
        printf("%d | ", s->data[i]);
    }
    printf("%d\n", s->data[s->height - 1]);
}

void push(Stack* s, int element) {
    s->data[s->height++] = element;
}

int pop(Stack* s) {
    return s->data[s->height--];
}