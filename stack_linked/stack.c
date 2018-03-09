#include "stack.h"

#include <stdio.h>
#include <stdlib.h>


Stack* initStack(Stack* stack)
{
    stack = (Stack*)malloc(sizeof(Stack));
    if(NULL == stack)
    {
        printf("Out of memory!\n");
        return;
    }
    stack -> top = NULL;

    return stack;
}


void pushStack(void* value, Stack* stack)
{
    if(NULL == value || NULL == stack) return;
    Node* pNew = (Node*)malloc(sizeof(Node));
    if(NULL == pNew)
    {
        printf("Out of memory!\n");
        return;
    }

    pNew -> element = value;
    pNew -> next = stack -> top;
    stack -> top = pNew;
}


void* popStack (Stack* stack)
{
    void* value = NULL;
    if(NULL == stack) return value;    

    if(!isEmptyStack(stack))
    {
        value = stack -> top -> element;
        Node* temp = stack -> top;
        stack -> top = temp -> next;

        free(temp);
    }

    return value;
}


int  isEmptyStack(Stack* stack)
{
    return ( NULL == stack || NULL == stack -> top );
}


void releaseStack(Stack* stack)
{
    if(NULL == stack) return;

    Node* temp;
    while((temp = stack -> top) != NULL)
    {
        stack -> top = temp -> next;
        free(temp);
    }

    free(stack);
    stack = NULL;
}
