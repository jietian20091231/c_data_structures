#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "student.h"

int main(void)
{
    Stack* stack;
    int index;

    stack = initStack(stack);

    puts("Push 5 elements into Stack:");

    for(index = 0; index < 5; index++)
    {
        char* name = (char*)calloc(10,sizeof(char));
        memset(name,0,sizeof(char));
        sprintf(name, "name_%d", index);

        Student* stu  = (Student*)malloc(sizeof(Student));
        stu -> id = index;
        stu -> name = name;

        printf("push [%d %p]%d %s.\n", index, stu, stu -> id, stu -> name);

        pushStack(stu, stack);
        
    }

    puts("\nPop elements from Stack:");

    void* p = NULL; 
    while((p = popStack(stack)) != NULL)
    {
        printf("pop [%p]%d, %s\n", p, ((Student*)p) -> id , ((Student*)p) -> name);
        free(((Student*)p) -> name);
        free(p);
    }

    puts("\nfree allocated memory!");
    releaseStack(stack);

    return 0;
}