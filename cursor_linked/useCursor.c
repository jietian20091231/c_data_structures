#include "cursor.h"
#include "student.h"

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 

int cmp(void* value_1, void* value_2);

void printCurosrLinkedInfo(const CursorLinked* pList);

int main()
{
    CursorLinked* pList = (CursorLinked*)malloc(sizeof(CursorLinked));

    initCursorLinked(pList, cmp);
    makeEmpty(pList);

    Student* stu_0 = (Student*)malloc(sizeof(Student));

    stu_0 -> id = 0;
    stu_0 -> name = "stu_0";

    int n = push(stu_0, pList, pList -> header);
    
    printCurosrLinkedInfo(pList);

    Student* stu_1 = (Student*)malloc(sizeof(Student));
    stu_1 -> id = 1;
    stu_1 -> name = "stu_1";

    push(stu_1, pList, pList -> rear);
    printCurosrLinkedInfo(pList);
    

    /*
    void* p = pop(pList);
    if(NULL != p)
    {
        Student* stu = (Student*)p;
        printf("student information:\n");
        printf("=======================\n");
        printf("Student[%d]%s\n", stu -> id, stu -> name);
        printf("=======================\n");        
    }

    printCurosrLinkedInfo(pList);
    */ 


    //free(pList);

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