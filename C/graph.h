typedef struct node {
    int data;
    int visited;
    struct node* next;
} Node;

typedef struct nodeList {
    Node* head;
} NodeList;

typedef struct graph {
    int capacity;
    NodeList* array;
} Graph;

Node* newNode(int data);
Graph* createGraph(int capacity);
void addEdge(Graph* g, int src, int data);
void printGraph(Graph* g);