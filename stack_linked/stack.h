#ifndef _STACK_H_
#define _STACK_H_

struct _node {
    void* element;
    struct _node* next; 
};

typedef struct _node Node;

struct _stack {
    Node* top;
};

typedef struct _stack Stack;

Stack* initStack(Stack* stack);
void pushStack(void* value, Stack* stack);
void* popStack (Stack* stack);
int  isEmptyStack(Stack* stack);
void releaseStack(Stack* stack);

#endif