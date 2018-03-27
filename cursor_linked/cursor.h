#ifndef CURSOR_H__
#define CURSOR_H__

#define CURSOR_SIZE 6

struct _node {
    void* element;
    int next;
    int prev;
};

typedef struct _node Node;

struct cursor_linked {
    Node cursorSpace[CURSOR_SIZE];
    int header;
    int front;
    int rear;
    int size;
    int (* _cmp) (void*, void*);
    
};

typedef int Position;

typedef struct cursor_linked CursorLinked;

Position cursorAlloc(CursorLinked* list);

void cursorFree(CursorLinked* list, Position pos);

void initCursorLinked(CursorLinked* list, int (* _cmp) (void*, void*));

void makeEmpty(CursorLinked* list);

int isEmpty(CursorLinked* list);

int isLast(CursorLinked* list, Position pos);

Position findPrevious(CursorLinked* list, void* value);

int push(void* value, CursorLinked* list, Position pos);

void* pop(CursorLinked* list);

Position header(CursorLinked* list);

Position first(CursorLinked* list);

void ShowCursorLinkedInfo(const CursorLinked* list, const char* msg);

void cursorDelete(void* value, CursorLinked* list);

void deleteList(CursorLinked* list);

#endif 