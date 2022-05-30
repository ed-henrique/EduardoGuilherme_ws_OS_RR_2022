#include <stdio.h>
#include "graph.h"

void DepthFirstSearchUtil(AdjListNode* head) {
    
    head->visited = 1;
    AdjListNode* tmp = head;

    printf("%d ", head->dest);

    while (tmp) {
        if (tmp->visited == 0) DepthFirstSearchUtil(tmp);
        tmp = tmp->next;
    }
}

void DepthFirstSearch(Graph* g) {
    for (int i = 0; i < g->V; i++) {
        if (g->array[i].head->visited == 0) DepthFirstSearchUtil(g->array[i].head);
    }
}

int main() {
    int V = 5;
    Graph* g = createGraph(V);
    addEdge(g, 0, 1);
    addEdge(g, 0, 4);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    addEdge(g, 2, 3);
    addEdge(g, 4, 3);

    printGraph(g);
    DepthFirstSearch(g);

    return 0;
}