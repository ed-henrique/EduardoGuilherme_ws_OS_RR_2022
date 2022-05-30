#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// This code was mostly taken from GeeksForGeeks

AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->visited = 0;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int V) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->array = (AdjList*)malloc(V * sizeof(AdjList));
    
    for (int i = 0; i < V; i++) g->array[i].head = NULL;
    
    return g;
}

void addEdge(Graph* g, int src, int dest) {
    AdjListNode* check = NULL;
    AdjListNode* newNode = newAdjListNode(dest);

    if (g->array[src].head == NULL) {
        newNode->next = g->array[src].head;
        g->array[src].head = newNode;
    } else {
        check = g->array[src].head;
        while (check->next != NULL) check = check->next;
        check->next = newNode;
    }

    newNode = newAdjListNode(src);
    if (g->array[dest].head == NULL) {
        newNode->next = g->array[dest].head;
        g->array[dest].head = newNode;
    } else {
        check = g->array[dest].head;
        while (check->next != NULL) check = check->next;
        check->next = newNode;
    }
}

void printGraph(Graph* g) {
    for (int i = 0; i < g->V; i++) {
        AdjListNode* pCrawl = g->array[i].head;
        printf("Adjacency list of vertex %d\n  >> head ", i);
        while (pCrawl) {
            printf("-> %d ", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n\n");
    }
}