#include "stack.h"
#include "student.h"

#include <stdio.h>
#include <stdlib.h>

int isEmptyStack(Stack stack)
{
    return (stack -> topOfStack == -1) ? 1 : 0 ;
}


int isFullStack(Stack stack)
{
    return (stack -> topOfStack + 1 == stack -> capacity) ? 1 : 0;
}


Stack createStack(int capacity)
{
    Stack stack;
    if(capacity <= 0)
    {
        printf("Stack's capacity is a integer more than zero");
        return NULL;
    }

    stack = (Stack) malloc(sizeof( struct _stack));
    if(NULL == stack)
    {
        printf("Out of memory!\n");
        return NULL;
    }

    stack -> array = (void **) malloc(sizeof(void *) * capacity);
    if( NULL == stack -> array )
    {
        printf("Out of memory!\n");
        return NULL;
    }

    stack -> capacity = capacity;
    stack -> topOfStack = -1;

    return stack;
}


void pushStack(void* value, Stack stack)
{
    if(NULL == value || NULL == stack )
    {
        printf("push value is NULL or stack pointer is NULL.\n");
        return;
    }

    if(isFullStack(stack))
    {
        printf("Stack is full, can't push again.\n");
        return;
    }

    printf("stack pushStack: [%p]%d, %s\n", value, ((Student*)value) -> id, ((Student*)value) -> name);

    stack -> array[ ++stack -> topOfStack ] = value;
    printf("stack -> topOfStack = %d\n", stack -> topOfStack);
}


void* popStack(Stack stack)
{
    if(isEmptyStack(stack))
    {
        puts("Stack is empty!\n");
        return NULL;
    }

    void* top = stack -> array[stack -> topOfStack];    
    stack -> topOfStack--;

    printf("stack pushStack: [%p]%d, %s\n", top, ((Student*)top) -> id, ((Student*)top) -> name);

    return top;
}
