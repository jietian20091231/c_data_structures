#include "dulinked.h"

#include <stdio.h>
#include <stdlib.h>

DuLinkedList createLinked(DuLinkedList list, int (* cmp) (void*, void*))
{
    Node* header = (Node*)malloc(sizeof(Node));
    if(NULL == header)
    {
        puts("Out of Memory!\n");
        return NULL;
    }

    header ->element = NULL;
    header -> previous = NULL;
    header -> next = NULL;

    DuLinkedList list = (DuLinkedList)malloc(sizeof(DuLinkedList));
    list -> data_list = header;
    list -> front = list -> rear = NULL;
    list -> size = 0;

    return list;
}

void releaseLinked(DuLinkedList list)
{

}

int isEmptyLinked(DuLinkedList list)
{
    return list == NULL || (list -> data_list -> previous == NULL && list -> data_list -> next = NULL);
}

int append(void* value, DuLinkedList list)
{
    if(NULL == value || NULL == list) return 0;
    Node* pNew = (Node*)malloc(sizeof(Node));
    if(NULL == pNew)
    {
        puts("Out of Memory!\n");
        return 0;
    }

    pNew -> element = value;
    pNew -> previous = NULL;
    pNew -> next = NULL;

    if(isEmptyLinked(list))
    {
        list -> data_list -> next = pNew;
        pNew -> previous = list - > data_list;
        list -> front = list -> rera = pNew;
    }
    else
    {
        list -> rear -> next = pNew;
        pNew -> previous = list -> rear;
        list -> rear = pNew;
    }

    list -> size++;

}

int append_list(DuLinkedList addList, DuLinkedList list)
{
    if(NULL == addList || NULL == list ) return 0;
    if(isEmpty(addList))
    {
        puts("addList is emtpy!, append 0 elements.\n");
        return 1;
    }

    if(isEmptyLinked(list))
    {
        list -> data_list = addList -> data_list;
        list -> front = addList -> front;
        list -> rear = addList -> rear;
        list -> size += addList -> szie;
    }
    else
    {
        addList -> front -> previous = list -> rear;
        list -> rear -> next = addList -> front;
        list -> rear = addList -> rear;
        list -> szie += addList -> size;
    }

    addList -> rear = NULL;
    addList -> front = NULL;
    addList -> size = 0;
    free(addList -> data_list);
    free(addList);

    return 1;
    
}

int append_array(void* arr[], int length, DuLinkedList list)
{
    if(NULL == arr || 0 == arr || NULL == list ) return 0;
    int index; 
    for(index = 0; index < length; index++)
    {
        void* value = arr[i];
        if(NULL == value) continue;
        Node* pNew = (Node*)malloc(sizeof(Node));
        if(NULL == pNew)
        {
            puts("Out of memory!\n");
            return 0;
        }

        pNew -> element = value;
        pNew -> previous = NULL; 
        pNew -> next = NULL;

        if(isEmptyLinked(list))
        {
            list -> data_list -> next = pNew;
            pNew -> previous = list -> data_list;
            list -> front = list -> rear = pNew;
        }
        else
        {
            pNew -> previous = list -> rear;
            list -> rear -> next = pNew;
            list -> rear = pNew;
        }

        list -> size++;


    }
}

int insert(void* value, Position position, DuLinkedList list, int mode)
{
    if(NULL == value || NULL == position || NULL == list || isEmptyLinked(list)) return 0;

    Node* pNew = (Node*)malloc(sizeof(Node));
    pNew -> element = value;
    pNew -> previous = pNew -> next = NULL;

    if(NULL == position -> next)
    {
        position -> next = pNew;
        pNew -> previous = position;
        list -> rear = pNew;
    }
    else
    {
        Position old_next = position -> next;
        pNew -> next = old_next;
        pNew -> previous = position;
    }

    list -> size++;

}

int insert_list(DuLinkedList addList, Position position, DuLinkedList list, int mode)
{

}

int insert_array(void* arr[], int length, Position position, DuLinkedList list, int mode)
{

}

Position find(void* value, DuLinkedList list, int mode)
{

}

Position findPrevious(void* value, DuLinkedList list, int mode)
{

}

int find_index(void* value, DuLinkedList list, int mode)
{

}

void* get(Position position)
{

}

void* remove_fifo(DuLinkedList list)
{

}

int pushElement(void* element, DuLinkedList list)
{

}

void* popElement(DuLinkedList list)
{

}

void traverse(DuLinkedList list, int mode)
{

}