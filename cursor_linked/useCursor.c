#include "cursor.h"
#include "student.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(void* value_1, void* value_2);

void printCurosrLinkedInfo(const CursorLinked* pList);

int main()
{
    CursorLinked* pList = (CursorLinked*)malloc(sizeof(CursorLinked));

    initCursorLinked(pList, cmp);
    makeEmpty(pList);

    int index;
    for(index = 0; index < CURSOR_SIZE - 2; index++)
    {
        char* name = (char*)calloc(10,sizeof(char));
        memset(name,0,sizeof(char));
        sprintf(name, "name_%d", index);
        printf("%s\n", name);

        Student* stu  = (Student*)malloc(sizeof(Student));
        stu -> id = index;
        stu -> name = name;

        printf("Student[%p, %d]%s\n", stu, stu -> id, stu -> name);

        push(stu, pList, pList -> rear);
    }

    printCurosrLinkedInfo(pList);

    Student* object = (Student*)malloc(sizeof(Student*) * 1);
    object -> id = 5;
    object -> name = "name_0";

    Position pos = find(pList, object);
    if(pos > 0)
    {
        printf("Student[%d]%s is found, it's index eq %d\n", object -> id, object -> name, pos);
    }
    else
    {
        printf("Student[%d]%s is not found, try another student again.\n", object -> id, object -> name);
    }

    free(object);

    void* p = pop(pList);
    while(NULL != p)
    {
        Student* stu = (Student*)p;
        printf("CursorLinked pop -> Student[%p %d]%s\n", stu, stu -> id, stu -> name);
        p = pop(pList);
    }

    printCurosrLinkedInfo(pList);

    clearCursorLinked(pList);

    printCurosrLinkedInfo(pList);

    free(pList);

    return 0;
}

int cmp(void* value_1, void* value_2)
{
    Student* stu_1 = (Student*) value_1;
    Student* stu_2 = (Student*) value_2;

    return stu_1 -> id - stu_2 -> id;    
}

void printCurosrLinkedInfo(const CursorLinked* pList)
{
    if(NULL != pList)
    {
        printf("=============== Cursor Linked list information ===============\n");
        printf("list -> header = %d;\n", pList -> header);
        printf("list -> front = %d;\n", pList -> front);
        printf("list -> rear = %d;\n", pList -> rear);
        printf("list -> size = %d.\n", pList -> size);                        
        printf("==============================================================\n");

        int index;
        for(index = 0; index < CURSOR_SIZE; index++)
        {
            Node node = pList -> cursorSpace[index];
            printf("cursor[%d].prev = %d, cursor[%d].next = %d, ", index, pList -> cursorSpace[index].prev, index, pList -> cursorSpace[index].next);
            if(NULL != node.element)            
            {
                Student* stu = (Student*)node.element;
                printf("cursor[%d].element = student[%d]%s\n", index, stu -> id, stu -> name);
            }
            else
            {
                printf("cursor[%d].element = NULL\n", index);                
            }

        }

        printf("========================  done  ===============================\n");

    }
}


void clearCursorLinked(CursorLinked* list)
{
    if(NULL == list) return;

    printf("clearCursorLinked\n");

    int index;
    for(index = 0; index < CURSOR_SIZE; index++)
    {
        if(NULL != list -> cursorSpace[index].element)
        {
            Student* stu = (Student*)(list -> cursorSpace[index].element);
            free(stu -> name);
            free(stu);
        }

        list -> cursorSpace[index].element = NULL;
        list -> cursorSpace[index].next = index + 1;
        list -> cursorSpace[index].prev = index -1;
    }

    list -> cursorSpace[CURSOR_SIZE -1].next = 0;
    list -> cursorSpace[list -> header].next = 0;
    list -> cursorSpace[list -> header].prev = -1;

    ShowCursorLinkedInfo(list, "releaseCursorLinked:");
}