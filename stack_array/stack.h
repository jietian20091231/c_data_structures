#ifndef _STACK_H_
#define _STACK_H_

struct _stack {
    int capacity;
    int topOfStack;
    void** array;
};

typedef struct _stack* Stack;

int isEmptyStack(Stack stack);
int isFullStack(Stack stack);
Stack createStack(int capacity);
void pushStack(void* value, Stack stack);
void* popStack(Stack stack);



#endif