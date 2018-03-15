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
    int status = (NULL == list || NULL == list -> data_list -> next)? 1 : 0;
    return status;
}

int append(void* value, DuLinkedList list, int mode)
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
        pNew -> previous = list -> data_list;
        list -> front = list -> rear = pNew;
    }
    else
    {
        if(0 == mode)
        {
            list -> rear -> next = pNew;
            pNew -> previous = list -> rear;
            list -> rear = pNew;            
        }
        else
        {
            Node* old_front = list -> front;

            list -> data_list -> next = pNew;
            pNew -> previous = list -> data_list;

            pNew -> next = old_front;
            old_front -> previous = pNew;

            list -> front = pNew;
        }
    }

    list -> size++;

}

int append_list(DuLinkedList addList, DuLinkedList list, int mode)
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
    }
    else
    {
        if(0 == mode)
        {
            addList -> front -> previous = list -> rear;
            list -> rear -> next = addList -> front;
            list -> rear = addList -> rear;
        }
        else
        {
            Node* old_list_front = list -> front;

            list -> data_list -> next = addList -> front;
            addList -> front -> previous = list -> data_list;

            addList -> rear -> next = old_list_front;
            old_list_front -> previous = addList -> rear;

            list -> front = addList -> front;

        }
    }

    list -> size += addList -> size;

    addList -> rear = NULL;
    addList -> front = NULL;
    addList -> size = 0;
    free(addList -> data_list);
    free(addList);

    return 1;
    
}

int append_array(void* arr[], int length, DuLinkedList list, int mode)
{
    if(NULL == arr || 0 == arr || NULL == list ) return 0;
    int index; 
    for(index = 0; index < length; index++)
    {
        void* value = arr[index];
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
            if(0 == mode)
            {
                pNew -> previous = list -> rear;
                list -> rear -> next = pNew;
                list -> rear = pNew;
            }
            else
            {
                Node* old_front = list -> front;

                list -> data_list -> next = pNew;
                pNew -> previous = list -> data_list;

                pNew -> next = old_front;
                old_front -> previous = pNew;

                list -> front = pNew;

            }

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

    if(0 == mode)
    {
        Node* old_next = position -> next;
        position -> next = pNew;
        pNew -> previous = position;
        if(NULL == old_next)
        {
            list -> rear = pNew;
        }
        else
        {
            pNew -> next = old_next;
            old_next -> previous = pNew;
        }
    }
    else
    {
        Node* old_previous = position -> previous;

        pNew -> next = position;
        position -> previous = pNew;

        old_previous -> next = pNew;
        pNew -> previous = old_previous;

        if(list -> data_list == old_previous)
        {
            list -> front = pNew;
        }
    }

    list -> size++;

}

int insert_list(DuLinkedList addList, Position position, DuLinkedList list, int mode)
{
    if(NULL == addList || NULL == position || NULL == list) return 0;

    if(0 == mode)
    {
        Node* old_next = position -> next;

        position -> next = addList -> front;
        addList -> front -> previous = position -> next;

        if(NULL == old_next)
        {
            list -> rear = addList -> rear;
        }
        else
        {
            addList -> rear -> next = old_next;
            old_next -> previous = addList -> rear;
        }
    }
    else
    {
        Node* old_previous = position -> previous;

        position -> previous  = addList -> front;
        addList -> front -> previous = position -> previous;

        addList -> rear -> next = position;
        position -> previous = addList -> rear;

        if(list -> data_list == old_previous)
        {
            list -> front = addList -> front;
        }

    }

    

    addList -> size = 0;
    addList -> front = NULL; 
    addList -> rear = NULL;

    free(addList -> data_list);
    free(addList);

    list -> size += addList -> size;

    return 1;

}

int insert_array(void* arr[], int length, Position position, DuLinkedList list, int mode)
{
    if(NULL == arr || 0 == length || NULL == position || isEmptyLinked(list)) return 0;
    int index;
    for(index =0; index < length; index++)
    {
        void* value = arr[index];
        Node* pNew = (Node*)malloc(sizeof(Node));
        pNew -> element = value;
        pNew -> next = pNew -> previous = NULL;

        if(0 == mode)
        {
            Node* old_next = position -> next;

            position -> next = pNew;
            pNew -> previous = position;

            if(NULL == old_next)
            {
                list -> rear = pNew;
            }
            else
            {
                pNew -> next = old_next;
                old_next -> previous = pNew;
            }

        }
    }

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