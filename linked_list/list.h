#ifndef _LIST_H_
#define _LIST_H_

struct _node {
    void* element;
    struct _node* next;
};

typedef struct _node Node;
typedef Node* Position;

struct _linkedList {
    Node* data_list;
    Position rear;
    int size;
    int (* _cmp) (void*, void*);
};

typedef struct _linkedList* LinkedList;

LinkedList createLinkedList(LinkedList list, int (* cmp) (void*, void*));

void releaseLinkedList(LinkedList list);

int isEmpty(LinkedList list);

int append(void* value, LinkedList list);

int append_list(LinkedList addList, LinkedList list);

int append_array(void* arr[], int length, LinkedList list);

int insert(void* value, Position position, LinkedList list);

int insert_list(LinkedList addList, Position position, LinkedList list);

int insert_array(void* arr[], int length, Position position, LinkedList list);

Position find(void* value, LinkedList list);

Position findPrevious(void* value, LinkedList list);

int find_index(void* value, LinkedList list);

void* get(Position position);

void* remove_fifo(LinkedList list);

#endif
