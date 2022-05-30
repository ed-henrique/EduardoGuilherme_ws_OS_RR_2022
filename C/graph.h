typedef struct adjListNode {
    int dest;
    int visited;
    struct adjListNode* next;
} AdjListNode;

typedef struct adjList {
    AdjListNode* head;
} AdjList;

typedef struct graph {
    int V;
    AdjList* array;
} Graph;

AdjListNode* newAdjListNode(int dest);
Graph* createGraph(int V);
void addEdge(Graph* g, int src, int dest);
void printGraph(Graph* g);