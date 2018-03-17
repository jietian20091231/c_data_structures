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

    header -> element = NULL;
    header -> previous = NULL;
    header -> next = NULL;

    list = (DuLinkedList)malloc(sizeof(struct _dulinkedList));
    list -> _cmp = cmp;
    list -> data_list = header;
    list -> front = list -> rear = NULL;
    list -> size = 0;

    return list;
}

void releaseLinked(DuLinkedList list)
{
    if(NULL == list) return;
    if(!isEmptyLinked(list))
    {
        puts("duLinked list is not emptry, please make sure the linked list is empty!\n");
        return;
    }

    list -> rear = NULL;
    list -> front = NULL;
    list -> data_list -> next = NULL;
    list -> data_list -> previous = NULL;
    list -> size = 0;
    list -> _cmp = NULL;

    free(list -> data_list);
    list -> data_list = NULL;

    free(list);
    list = NULL;
}

int isEmptyLinked(DuLinkedList list)
{
    int status = (NULL == list || NULL == list -> data_list -> next)? 1 : 0;
    return status;
}

int append(void* value, DuLinkedList list, int mode)
{
    if(NULL == value || NULL == list) return -1;
    Node* pNew = (Node*)malloc(sizeof(Node));
    if(NULL == pNew)
    {
        puts("Out of Memory!\n");
        return -1;
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

    return list -> size++;

}

int append_list(DuLinkedList addList, DuLinkedList list, int mode)
{
    if(NULL == addList || NULL == list ) return -1;
    if(isEmptyLinked(addList))
    {
        puts("addList is emtpy!, append 0 elements.\n");
        return list -> size;
    }

    if(isEmptyLinked(list))
    {
        list -> data_list -> next = addList -> front;
        addList -> front -> previous = list -> data_list;
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

    return list -> size;
    
}

int append_array(void* arr[], int length, DuLinkedList list, int mode)
{
    if(NULL == arr || 0 == arr || NULL == list ) return -1;
    int index; 
    for(index = 0; index < length; index++)
    {
        void* value = arr[index];
        if(NULL == value) continue;
        Node* pNew = (Node*)malloc(sizeof(Node));
        if(NULL == pNew)
        {
            puts("Out of memory!\n");
            return -1;
        }

        pNew -> element = value;
        pNew -> previous = NULL; 
        pNew -> next = NULL;

        //printf("[%d]loop ===> list -> front = %p, list -> rear = %p, list -> data_list -> next = %p\n", index ,list ->front, list -> rear ,list -> data_list -> next);
        if(isEmptyLinked(list))
        {
            printf("list is empty!\n");
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
                //printf("list -> front = %p, list -> data_list -> next = %p\n", list ->front, list -> data_list -> next);
            }
            else
            {
                //printf("list -> front = %p\n list -> data_list = %p\n", list -> front , list -> data_list);
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

    return list -> size;
}

int insert(void* value, Position position, DuLinkedList list, int mode)
{
    if(NULL == value || NULL == position || NULL == list || isEmptyLinked(list)) return -1;

    Node* pNew = (Node*)malloc(sizeof(Node));
    if(NULL == pNew)
    {
        puts("Out of memory!\n");
        return -1;
    }

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

    return list -> size;

}

int insert_list(DuLinkedList addList, Position position, DuLinkedList list, int mode)
{
    if(NULL == addList || NULL == position || NULL == list) return -1;

    if(0 == mode)
    {
        Node* old_next = position -> next;

        position -> next = addList -> front;
        addList -> front -> previous = position;

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

        old_previous -> next = addList -> front;
        addList -> front -> previous = old_previous;

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

    return list -> size;

}

int insert_array(void* arr[], int length, Position position, DuLinkedList list, int mode)
{
    if(NULL == arr || 0 == length || NULL == position || isEmptyLinked(list)) return -1;
    int index;
    for(index =0; index < length; index++)
    {
        void* value = arr[index];
        if(NULL == value) continue;

        Node* pNew = (Node*)malloc(sizeof(Node));
        if(NULL == pNew)
        {
            puts("Out of Memory!\n");
            return -1;
        }

        pNew -> element = value;
        pNew -> next = pNew -> previous = NULL;

        if(0 == mode)
        {
            Node* old_next = position -> next;

            position -> next = pNew;
            pNew -> previous = position;

            if(NULL == old_next)
            {
                list -> rear -> next;
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

            old_previous -> next = pNew;
            pNew -> previous = old_previous;

            pNew -> next = position;
            position -> previous = pNew;

            if(list -> data_list == old_previous) list -> front = pNew;
        }

        list -> size++;
    }

    return list -> size;
}

Position find(void* value, DuLinkedList list, int mode)
{
    if(NULL == value || NULL == list || NULL == list -> _cmp) return NULL;

    Position p;

    if(0 == mode)
    {
        p = list -> front;
        while(p && 0 != list -> _cmp(value, p -> element)) p = p -> next;
    }
    else
    {
        p = list -> rear;
        while(list -> data_list != p && 0 != list -> _cmp(value, p -> element)) p = p -> previous;

        if(list -> data_list == p) p = NULL;      

    }

    return p;

}

Position findPrevious(void* value, DuLinkedList list, int mode)
{
    if(NULL == value || NULL == list || NULL == list -> _cmp) return NULL;

    Position p;

    if(0 == mode)
    {
        p = list -> front;
        while(p && p ->next &&  0 != list -> _cmp(value, p -> next -> element)) p = p -> next;
    }
    else
    {
        p = list -> rear;
        while(list -> data_list != p -> previous && 0 != list -> _cmp(value, p -> previous -> element)) p = p -> previous;
        if(list -> front == p) p = NULL;      

    }

    return p;
}

int find_index(void* value, DuLinkedList list)
{
    if(NULL == value || NULL == list || NULL == list -> _cmp) return -1;

    int index = -1;

    Position p = list -> rear;
    index = list -> size -1;
    while(list -> data_list != p && 0 != list -> _cmp(value, p -> element))
    {
        p = p -> previous;
        index--;
    }
    
    if(list -> data_list == p)
    {
        p = NULL;      
        index = -1;
    }

    return index;
}

void* get(Position position)
{
    if(NULL == position) return NULL;
    return position -> element;
}

void* rpop(DuLinkedList list)
{
    if(NULL == list || NULL == list -> data_list || isEmptyLinked(list)) return NULL;

    Node* old_rear = list -> rear;

    list -> rear = old_rear -> previous;
    list -> rear -> next = NULL;

    //printf("pop rear old_rear = %p\n", old_rear);

    void* result = old_rear -> element;
    free(old_rear);
    old_rear = NULL;

    if(list -> rear == list ->data_list)
    {
        list -> front = NULL;
        list -> rear  = NULL;
    }

    list -> size--;

    return result;
}

void* lpop(DuLinkedList list)
{
    if(NULL == list || NULL == list -> data_list || isEmptyLinked(list)  ) return NULL;

    Node* old_front = list -> front;
    Node* new_front = list -> front -> next;
    if(NULL == new_front)
    {
        list -> data_list -> next = NULL;
        list -> front = list -> rear = NULL;
    }
    else
    {
        list -> data_list -> next = new_front;
        new_front -> previous = list -> data_list;
        list -> front = new_front;
    }
    
    void* result = old_front -> element;
    free(old_front);
    
    list -> size--;

    return result;    
}

int rpush(void* value, DuLinkedList list)
{
    if(NULL == value || NULL == list) return -1;
    Node* pNew = (Node*)malloc(sizeof(Node));
    if(NULL == pNew)
    {
        puts("Out of Memory!\n");
        return -1;
    }

    pNew -> element = value;
    pNew -> previous = pNew -> next = NULL;

    if(isEmptyLinked(list))
    {
        printf("list is emptry!\n");
        list -> data_list -> next = pNew;
        pNew -> previous = list -> data_list;
        list -> front = list -> rear = pNew;
    }
    else
    {
        list -> rear -> next = pNew;
        pNew -> previous = list -> rear;
        list -> rear = pNew;
    }

    list -> size++;

    return list -> size;

}

int lpush(void* value, DuLinkedList list)
{
    if(NULL == value || NULL == list ) return -1;
    Node* pNew = (Node*)malloc(sizeof(Node));
    if(NULL == pNew)
    {
        puts("Out of memory!\n");
        return -1;
    }

    pNew -> element = value;
    pNew -> previous = pNew -> next = NULL;

    //printf("isEmtpty = %d\n", isEmptyLinked(list));

    if(isEmptyLinked(list))
    {
        list -> data_list -> next = pNew;
        pNew -> previous = list -> data_list;
        list -> front = list -> rear = pNew;
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

    list ->size++;


    return list -> size;

}
