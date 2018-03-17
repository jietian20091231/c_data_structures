#include "dulinked.h"

#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearLinkedList(DuLinkedList list);
int cmp(void* v1, void* v2);
void printListInfo(int size, Node* front, Node* rear);
void printElementInfo(void* current);

int main(void)
{
    DuLinkedList list;
    list = createLinked(list,cmp);

    int index;
    for(index = 0; index < 5; index++)
    {
        char* name = (char*)calloc(10, sizeof(char));
        memset(name, 0, sizeof(char));
        sprintf(name, "name_%d", index);

        Student* stu = (Student*)malloc(sizeof(Student));
        stu -> id = index;
        stu -> name = name;        
        printf(">>>>==== Student[%p %d]%s.\n", stu, stu -> id, stu -> name);

        int n = append(stu, list, 0);

        printf(">>>>==== append mode 0 successed, current list's size is %d\n", n);

        printListInfo(list -> size, list -> front, list -> rear);        
    }

    puts("================ test funtions find, find_index, findPrevious ================");
    Student* stu_find = (Student*)malloc(sizeof(Student));
    stu_find -> id = 4;
    stu_find -> name = "name_4";

    Position p = find(stu_find,list,1);
    if(p)
    {
        Student* st = (Student*) (p -> element);
        printf("student is found, student[%p, %p] information: %d, %s\n", p, st, st -> id, st -> name);
    }
    else
    {
        printf("student[%d]%s isn't found.\n", stu_find -> id, stu_find -> name);
    }
    
    int stuIndex = find_index(stu_find, list);

    printf("====> student[%d]%s is found, index = %d\n", stu_find ->id, stu_find -> name, stuIndex);

    p = findPrevious(stu_find, list, 0);
    if(p)
    {
        Student* st = (Student*) (p -> element);
        printf("student's previous is found, student[%p, %p] information: %d, %s\n", p, st, st -> id, st -> name);
    }
    else
    {
        printf("student[%d]%s's previous isn't found.\n", stu_find -> id, stu_find -> name);
    }

    free(stu_find);



    printf("================  clear double linked list  ================\n"); 
    clearLinkedList(list);

    printf("====<<<< list -> front = %p, list -> rear = %p, list -> data_list = %p\n", list -> front, list -> rear , list -> data_list);

    printListInfo(list -> size, list -> front, list -> rear);
    releaseLinked(list);

    return 0;
}

void clearLinkedList(DuLinkedList list)
{
    void* p;
    while((p = rpop(list)) != NULL)
    {
        Student* stu = (Student*)p;
        //printf("student[%p, %d]%s\n", p, stu -> id , stu -> name);
        
        free(stu -> name);
        free(stu);
    }
}


int cmp(void* value_1, void* value_2)
{
    Student* stu_1 = (Student*) value_1;
    Student* stu_2 = (Student*) value_2;

    printf("stu_1[%p] -> id - stu_2[%p] ->id = %d\n", stu_1, stu_2, stu_1 -> id - stu_2 -> id);

    return stu_1 -> id - stu_2 -> id;
}


void printListInfo(int size, Node* front, Node* rear)
{
    //printf("front = %p, rear = %p.\n", front, rear);
    //printf("front -> element = %p, rear -> element = %p\n", front -> element, rear -> element);
    Student* stu_front = NULL;
    Student* stu_rear = NULL;

    printf("===<<< list info :\n");

    if( front && front -> element != NULL)
    {
        stu_front = (Student*) (front -> element);
        printf("===<<< list -> front [%p, %d]%s\n", front -> element, stu_front -> id, stu_front -> name);
    }
    else
    {
        printf("===<<< list -> front [%p]\n", NULL);
    }

    if( rear && rear -> element != NULL)
    {
        stu_rear = (Student*)(rear -> element);
        printf("===<<< stu_rear = %p\n", stu_rear);
        printf("===<<< list -> rear [%p, %d]%s\n", rear -> element, stu_rear -> id, stu_rear -> name);    
    }
    else
    {
        printf("===<<< list -> rear [%p]\n", NULL);
    }
    
    
    printf("===<<< list -> size = %d\n", size);    
}

void printElementInfo(void* current)
{
    if(NULL == current)
    {
        printf("====<<<< current is NULL.\n");
        return;
    }

    Student* stu = (Student*)current;
    printf("====<<<< Student[%p, %d]%s\n", current, stu -> id, stu -> name);
}