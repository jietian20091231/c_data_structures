#include <stdio.h>
#include <stdlib.h>

#include "list.h"

LinkedList  createLinkedList(LinkedList list, int (* cmp)(void*, void*))
{
    Node* data_list = (Node*) malloc(sizeof(Node));
    if(data_list == NULL)
    {
        printf("Out of memory\n");
        return NULL;
    }

    data_list -> element = NULL;
    data_list -> next = NULL;

    list = (LinkedList)malloc(sizeof(struct _linkedList));

    list -> data_list = data_list;
    list ->rear = NULL;
    list -> _cmp = cmp;
    list -> size = 0;

    return list;

}

void releaseLinkedList(LinkedList list)
{
    
}


int isEmptry(LinkedList list)
{
    return list -> data_list -> next == NULL;
}

int append(void* value, LinkedList list)
{
    Node* pNew = (Node*) malloc(sizeof(Node));
    if(NULL == pNew)
    {
        printf("Out of memory!\n");
        return 0;
    }

    pNew -> element = value;
    pNew -> next = NULL;

    printf(" append: %p\n", pNew);

    if( NULL == list -> rear)
    {
        //printf("linked list is empty!\n");
        list -> data_list = pNew;
        list -> rear = pNew;
    }
    else
    {
        //printf("append element in the end\n"); 
        list -> rear -> next = pNew;
        list -> rear = pNew;

    }

    list -> size++;

    return 1;
}

int append_list(LinkedList addList, LinkedList list)
{
    list -> size += addList -> size;
    list -> rear -> next = addList -> data_list;
    list -> rear = addList -> rear;

    return 1;
}

int append_array(void* arr[], int length, LinkedList list)
{
    int index;
    for(index = 0 ; index < length; index++)
    {
        Node* pNew = (Node*)malloc(sizeof(Node));
        if(NULL == pNew)
        {
            printf("Out of memory!\n");
            return 0;
        }

        pNew -> element = arr[index];
        pNew -> next = NULL;

        printf("append_array : %p\n", list -> rear);

        if(NULL == list -> rear)
        {
            list -> data_list = pNew;
            list -> rear = pNew;
        }
        else
        {
            list -> rear -> next = pNew;
            list -> rear = pNew;
        }
        
        list -> size++ ;

    }

    return 1;
}

int insert(void* value, Position position, LinkedList list)
{
    if(NULL == position || NULL == value || NULL == list) return 0;
    Node * pNew = (Node*)malloc(sizeof(Node));
    if(NULL == pNew)
    {
        printf("Out of memory!\n");
        return 0;
    }

    pNew -> element = value;
    pNew -> next = NULL;

    if(NULL == position -> next)
    {
        position -> next = pNew;
        list -> rear  = pNew;
    }
    else
    {
        Position temp = position -> next;
        position -> next = pNew;
        pNew ->next = temp;
    }

    list -> size++;

    return 1;
}

int insert_list(LinkedList addList, Position position, LinkedList list)
{
    if(NULL == addList || NULL == position || NULL == list) return 0;

    if(NULL == position -> next)
    {
        position -> next =  addList -> data_list;
        list -> rear  = addList -> rear;
    }
    else
    {
        Position temp = position -> next;
        position -> next = addList -> data_list;
        addList -> rear -> next = temp;
    }

    list -> size += addList -> size;

    return 1;
}

int insert_array(void* arr[], int length, Position position, LinkedList list)
{
    if(NULL == position || NULL == list) return 0;
    int index;
    for( index = 0; index < length; index++ )
    {
        Node* pNew = (Node*)malloc(sizeof(Node));
        if(NULL == pNew)
        {
            printf("Out of memory!\n");
            return 0;
        }

        pNew -> element = arr[index];
        pNew -> next = NULL;

        if(NULL == position -> element)
        {
            position -> next  = pNew;
            list -> rear = pNew;
        }
        else
        {
            Position temp = position -> next;
            position -> next = pNew;
            pNew -> next = temp;
        }
    }

    return 1;
}

Position find(void* value, LinkedList list)
{
    Node* data_list = list -> data_list;
    Position p  = data_list;
    while( p && 0 != list -> _cmp(value, p -> element))
        p = p -> next;

    return p;
}

Position findPrevious(void* value, LinkedList list)
{
    Node* data_list = list -> data_list;
    Position p = data_list;

    while(p && p -> next && 0 != list -> _cmp(value, p-> next -> element))
        p = p -> next;

    return p;
}

int find_index(void* value, LinkedList list)
{
    int result = -1, index = 0;
    Node* data_list = list -> data_list;
    Position p = data_list;

    while(1)
    {
        if(NULL == p)
        {
            return -1;
        }

        if(0 == list -> _cmp(value, p -> element))
        {
            result = index;
            break;
        }

        index++;
        p = p -> next;
    }



    return result;
}

void* get(Position position)
{
    return position -> element;
}

void* remove_fifo(LinkedList list)
{
    if(NULL == list || NULL == list -> data_list  ) return NULL;
    Position temp = list -> data_list;
    list -> data_list = temp -> next;
    void* result = temp -> element;
    free(temp);

    list -> size--;

    return result;

}
