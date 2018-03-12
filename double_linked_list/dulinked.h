#ifndef _DULINKED_H_
#define _DULINKED_H_

struct _node {
    void* element;
    struct _node* next;
    struct _node* previous;
};

typedef struct _node Node;
typedef Node* Position;

struct _dulinkedList {
    Node* data_list;
    Position rear;
    Position front;
    int size;
    int (* _cmp) (void*, void*);
};

typedef struct _dulinkedList* DuLinkedList;

DuLinkedList createLinked(DuLinkedList list, int (* cmp) (void*, void*));

void releaseLinked(DuLinkedList list);

int isEmptyLinked(DuLinkedList list);

int append(void* value, DuLinkedList list, int mode);

int append_list(DuLinkedList addList, DuLinkedList list, int mode);

int append_array(void* arr[], int length, DuLinkedList list, int mode);

int insert(void* value, Position position, DuLinkedList list, int mode);

int insert_list(DuLinkedList addList, Position position, DuLinkedList list, int mode);

int insert_array(void* arr[], int length, Position position, DuLinkedList list, mode);

Position find(void* value, DuLinkedList list, int mode);

Position findPrevious(void* value, DuLinkedList list, int mode);

int find_index(void* value, DuLinkedList list, int mode);

void* get(Position position);

void* remove_fifo(DuLinkedList list);

int pushElement(void* element, DuLinkedList list);

void* popElement(DuLinkedList list);

void traverse(DuLinkedList list, int mode);



#endif