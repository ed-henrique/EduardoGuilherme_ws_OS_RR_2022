#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// This code was mostly taken from GeeksForGeeks

Node* newNode(int data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->visited = 0;
    n->next = NULL;
    return n;
}

Graph* createGraph(int capacity) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->capacity = capacity;
    g->array = (NodeList*)malloc(capacity * sizeof(NodeList));
    for (int i = 0; i < capacity; i++) g->array[i].head = NULL;
    return g;
}

void addEdge(Graph* g, int src, int data) {
    Node* check = NULL;
    Node* n = newNode(data);

    if (g->array[src].head == NULL) {
        n->next = g->array[src].head;
        g->array[src].head = n;
    } else {
        check = g->array[src].head;
        while (check->next != NULL) check = check->next;
        check->next = n;
    }

    n = newNode(src);
    if (g->array[data].head == NULL) {
        n->next = g->array[data].head;
        g->array[data].head = n;
    } else {
        check = g->array[data].head;
        while (check->next != NULL) check = check->next;
        check->next = n;
    }
}

void printGraph(Graph* g) {
    for (int i = 0; i < g->capacity; i++) {
        Node* pCrawl = g->array[i].head;
        printf("Adjacency list of vertex %d\n  >> head ", i);
        while (pCrawl) {
            printf("-> %d ", pCrawl->data);
            pCrawl = pCrawl->next;
        }
        printf("\n\n");
    }
}