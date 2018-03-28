#include "cursor.h"
#include "stdio.h"


static int checkCursorLinked(CursorLinked* list);
static int checkLinkedAndPos(CursorLinked* list, Position pos);


Position cursorAlloc(CursorLinked* list)
{
    if(checkCursorLinked(list)) return -1;

    Position p = list -> cursorSpace[0].next;
    list -> cursorSpace[0].next = list -> cursorSpace[p].next;
    printf("list -> cursorSpace[0].next = %d\n", list -> cursorSpace[0].next);

    return p;

}


void cursorFree(CursorLinked* list, Position pos)
{
    if(checkLinkedAndPos(list, pos)) return;

    list -> cursorSpace[pos].next = list -> cursorSpace[0].next;
    list -> cursorSpace[pos].prev = -1;

#ifndef DEBUG
    printf("CursorFree =====> cursor[%d].next = %d\n", pos, list -> cursorSpace[pos].next);
#endif

    list -> cursorSpace[0].next = pos;

#ifndef DEBUG
    printf("CursorFree =====> cursor[0].next = %d\n", list -> cursorSpace[0].next);
#endif    

}


void initCursorLinked(CursorLinked* list, int (* _cmp) (void*, void*))
{
    if(checkCursorLinked(list)) return;

    list -> size = list -> front = list -> rear = list -> header = 0;
    list -> _cmp = _cmp;

    int i;
    for(i = 0; i < CURSOR_SIZE; i++)
    {
        list -> cursorSpace[i].next = i + 1;
        list -> cursorSpace[i].prev = i - 1;
    }

    list -> cursorSpace[CURSOR_SIZE -1 ].next = 0;
        

#ifndef DEBUG
    ShowCursorLinkedInfo(list,"initCursorLinked");
#endif
    
}


void makeEmpty(CursorLinked* list)
{
    if(checkCursorLinked(list))
    {
        printf("makeEmpty: deleteList\n");
        deleteList(list);
    }
        
    ShowCursorLinkedInfo(list,"makeEmpty(1)");

    Position header = cursorAlloc(list);
    printf("header = %d\n", header);
    if( 0 == header) puts("Out of memory!\n");
    list -> cursorSpace[header].next = 0;
    list -> cursorSpace[header].prev = -1;
    list -> header = header;
    list -> front = list -> rear = header;

    ShowCursorLinkedInfo(list, "makeEmpty(2)");
}


int isEmpty(CursorLinked* list)
{
    return ( 1 == checkCursorLinked(list) || 0 == list -> cursorSpace[list -> header].next) ? 1 : 0;
}


int isLast(CursorLinked* list, Position pos)
{
    int result =  ( 0 == checkLinkedAndPos(list, pos) && 0 == list -> cursorSpace[pos].next ) ? 1 : 0;
    printf("isLast = %d\n", result);
    printf("list -> cursorSpace[%d].next = %d\n", pos, list -> cursorSpace[pos].next);
    return result;
}


Position findPrevious(CursorLinked* list, void* value)
{
    Position p = -1;
    if(checkCursorLinked(list)) return p;
    if(NULL == value || NULL == list -> _cmp) return p;
    p = list -> header;
    while(p && 0 != list -> _cmp(value ,list -> cursorSpace[list -> cursorSpace[p].next].element))
            p = list -> cursorSpace[p].next;

    return p;
}


Position find(CursorLinked* list, void* value)
{
    Position p = -1;
    if(checkCursorLinked(list)) return p;
    if(NULL == value || NULL == list -> _cmp) return p;
    p = list -> cursorSpace[list -> header].next;
    while(p && 0 != list -> _cmp(value, list ->cursorSpace[p].element))
        p = list -> cursorSpace[p].next;


    return p;
}


int push(void* value, CursorLinked* list, Position pos)
{
    if(checkLinkedAndPos(list, pos) || NULL == value) return -1;
    Position pNew = cursorAlloc(list);
    printf("pNew = %d\n", pNew);
    if(0 == pNew)
    {
#ifndef DEBUG
        printf("push : cursor linked list is FULL!\n");
#endif
        return -1;
    }

    list -> cursorSpace[pNew].element = value;
    list -> cursorSpace[pNew].next = list -> cursorSpace[pos].next;

    if(isEmpty(list))
    {
#ifndef DEBUG
        puts("push :curosr list is empty, list -> front = list -> rear = pNew.\n");
#endif // !
        list -> front = list -> rear = pNew;
    }
    else if(isLast(list,pNew))
    {
#ifndef DEBUG
        puts("push : pNew is the last of cursor list, list -> rear = pNew.\n");
#endif
        list -> rear = pNew;
    }

    list -> cursorSpace[pos].next = pNew;
    list -> cursorSpace[pNew].prev = pos;    

    list -> size++;
    
    return list -> size;
}


void* pop(CursorLinked* list)
{
    if(checkCursorLinked(list) || isEmpty(list)) return NULL;
    Position temp = list -> rear;
    Position prev = list -> cursorSpace[list -> rear].prev;

    list -> cursorSpace[prev].next = 0;
    list -> rear = prev;

    if(prev == list -> header)
    {
        list -> front = prev;
    }


    cursorFree(list, temp);
    list -> size--;

    return list -> cursorSpace[temp].element;
}


Position header(CursorLinked* list)
{
    if(checkCursorLinked(list)) return -1;
    return list -> header;
}


Position first(CursorLinked* list)
{
    if(checkCursorLinked(list)) return -1;
    return list -> cursorSpace[list -> header].next;
}


void ShowCursorLinkedInfo(const CursorLinked* list, const char* msg)
{
    if( NULL == &list)
    {
        printf("CursorLinked list is NULL.\n");
        return;
    }

    puts("<============================================>");
    printf("%s:\n", msg);
    printf("-------------------------\n");
    int index;
    for(index = 0; index < CURSOR_SIZE; index++)
    {
        printf("cursor[%d].next = %d, cursor[%d].prev = %d\n", index, list -> cursorSpace[index].next, index, list -> cursorSpace[index].prev);
    }
    puts("<============================================>");
}


static int checkCursorLinked(CursorLinked* list)
{
    if(NULL == list)
    {
#ifndef DEBUG
        puts("Cursor linked list is empty.\n");
#endif
        return 1;
    }

    return 0;
}


static int checkLinkedAndPos(CursorLinked* list, Position pos)
{
    if(checkCursorLinked(list))
    {
        return 1;
    }

    if( pos < 0 || pos > CURSOR_SIZE -1)
    {
#ifndef DEBUG
        printf("%d not in [0, %d]", pos, CURSOR_SIZE -1);
#endif
        return 1;
    }

    return 0;
}


void cursorDelete(void* value, CursorLinked* list)
{
    if(NULL == value || checkCursorLinked(list) || isEmpty(list)) return;
    Position p = findPrevious(list, value);
    if(!isLast(list, p))
    {
        list -> cursorSpace[p].next = list -> cursorSpace[list -> cursorSpace[p].next].next;
        list -> cursorSpace[list -> cursorSpace[p].next].prev = p;
        Position temp = list -> cursorSpace[p].next;

        if(isLast(list, temp))
        {
            if(list -> header == p)
            {
                list -> front = list -> rear = list -> header;
            }
        }
        else if(list -> header == p)
        {
            list -> front = list -> cursorSpace[p].next;
        }

        cursorFree(list, temp);
        list -> size--;

        ShowCursorLinkedInfo(list, "cursorDelete:");

    }
    
}

void deleteList(CursorLinked* list)
{
    if(checkCursorLinked(list)) return;

    Position p, temp;
    p = list -> cursorSpace[list -> header].next;
    list -> cursorSpace[list -> header].next = 0;
    list -> cursorSpace[list -> header].prev = -1;

#ifndef DEBUG
    printf("deleteList [header] header = %d, p = %d, cursorSpace[%d].next = %d\n", list -> header, p, p, list -> cursorSpace[p].next);
#endif // !    

    int count = 0;
    while( p != 0)
    {
        temp = list -> cursorSpace[p].next;
#ifndef DEBUG
        printf("deleteList[%d] p = %d, temp = %d, cursor[%d].prev = %d, cursor[%d].next = %d\n", count++, p, temp, temp, list -> cursorSpace[temp].prev, temp, list -> cursorSpace[temp].next);
#endif        
        cursorFree(list,temp);
        temp = p;
    }

    list -> size = 0;
    list -> front = list -> rear = list -> header;

}