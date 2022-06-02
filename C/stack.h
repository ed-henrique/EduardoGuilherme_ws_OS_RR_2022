typedef struct stack {
    long height;
    long capacity;
    long* data;
} Stack;

Stack* createStack(long capacity);
void destroyStack(Stack** s_ref);
int stackIsEmpty(Stack* s);
void printStack(Stack* s);
void push(Stack* s, long element);
long pop(Stack* s);