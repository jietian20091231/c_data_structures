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
    DuLinkedList list_1;
    DuLinkedList list_2;
    list = createLinked(list,cmp);
    printf("list -> data_list = %p\n", list -> data_list );

    list_1 = createLinked(list_1, cmp);
    list_2 = createLinked(list_2, cmp);


    printf("================  append mode = 1 list_1  ================\n");

    int index;
    for(index = 0; index < 3; index++)
    {
        char* name = (char*)calloc(10, sizeof(char));
        memset(name, 0, sizeof(char));
        sprintf(name, "name_%d", index);

        Student* stu = (Student*)malloc(sizeof(Student));
        stu -> id = index;
        stu -> name = name;        
        printf(">>>>==== Student[%p %d]%s.\n", stu, stu -> id, stu -> name);

        int n = append(stu, list_1, 1);

        printf(">>>>==== append mode 1 successed, current list's size is %d\n", n);

        printListInfo(list_1 -> size, list_1 -> front, list_1 -> rear);
    }

    printf("==============  append mode = 1 list_1  done  ==============\n");

    printf("================  append mode = 1 list_2  ================\n");

    for(index = 3; index < 6; index++)
    {
        char* name = (char*)calloc(10, sizeof(char));
        memset(name, 0, sizeof(char));
        sprintf(name, "name_%d", index);

        Student* stu = (Student*)malloc(sizeof(Student));
        stu -> id = index;
        stu -> name = name;        
        printf(">>>>==== Student[%p %d]%s.\n", stu, stu -> id, stu -> name);

        int n = append(stu, list_2, 1);

        printf(">>>>==== append mode 1 successed, current list's size is %d\n", n);

        printListInfo(list_2 -> size, list_2 -> front, list_2 -> rear);
    }    
    printf("==============  append mode = 0 list_2  done  ==============\n");

    printf("============== append list mode = 0 (append list_1, list_2 to list) ==============\n");
    append_list(list_1, list, 1);
    printListInfo(list -> size, list -> front, list -> rear);
    append_list(list_2, list, 1);
    printListInfo(list -> size, list -> front, list -> rear);
    printf("============== append list mode = 0 (append list_1, list_2 to list) done ==============\n");


    printf("================  rpop  ================\n"); 
    void* current;
    while((current = rpop(list)))
    {
        printf("====<<<< list -> front = %p, list -> rear = %p.\n", list -> front, list -> rear);
        printListInfo(list -> size, list ->front, list -> rear);
        printElementInfo(current);

        Student* temp = (Student*)current;
        free(temp -> name);
        free(temp);
    }
    printf("====<<<< list -> front = %p, list -> rear = %p, list -> data_list = %p\n", list -> front, list -> rear , list -> data_list);

    printListInfo(list -> size, list -> front, list -> rear);

    clearLinkedList(list);
    releaseLinked(list);

    return 0;
}

void clearLinkedList(DuLinkedList list)
{
    void* p;
    //printf("p = %p\n", p);    
    while((p = rpop(list)) != NULL)
    {
        Student* stu = (Student*)p;
        printf("student[%p, %d]%s\n", p, stu -> id , stu -> name);
        
        free(stu -> name);
        free(stu);
    }
}


int cmp(void* value_1, void* value_2)
{
    Student* stu_1 = (Student*) value_1;
    Student* stu_2 = (Student*) value_2;

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