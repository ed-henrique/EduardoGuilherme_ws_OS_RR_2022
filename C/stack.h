typedef struct stack {
    int height;
    int capacity;
    int* data;
} Stack;

Stack* createStack(int capacity);
void printStack(Stack* s);
void push(Stack* s, int element);
int pop(Stack* s);