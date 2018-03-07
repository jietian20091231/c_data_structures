#include "stack.h"
#include "student.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void releaseStack(Stack stack);
void cleanStack(Stack stack);

int main(void)
{
    Stack stack;

    stack = createStack(10);

    printf("stack -> capacity = %d\n", stack -> capacity);

    
    int index;

    for(index = 0; index < 10; index++)
    {
        char* name = (char*)calloc(10,sizeof(char));
        memset(name,0,sizeof(char));
        sprintf(name, "name_%d", index);
        printf("%s\n", name);

        Student* stu  = (Student*)malloc(sizeof(Student));
        stu -> id = index;
        stu -> name = name;

        printf("[%d %p]%d %s.\n", index, stu, stu -> id, stu -> name);

        pushStack(stu, stack);

    }

    void* pop;
    while((pop = popStack(stack) ) != NULL)
    {
        printf("[%p]%d, %s\n", pop, ((Student *)pop) -> id, ((Student *) pop) -> name );
        free(((Student*)pop) -> name);
        free(pop);
    }
    
    return 0;
}

void releaseStack(Stack stack)
{
    if(isEmptyStack(stack))
    {
        free(stack -> array);
        stack -> capacity = 0;
        stack -> topOfStack = -1;
        free(stack);
        stack = NULL;
    }
}


void cleanStack(Stack stack)
{
    if(isEmptyStack(stack)) return;

    while(stack -> topOfStack != -1 )
    {
        void* top = stack -> array[stack -> topOfStack];
        free(top);
        top = NULL;
        stack -> topOfStack--;
    }
}