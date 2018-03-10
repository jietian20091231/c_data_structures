# c_data_structures
data_structures (C description)

## linked list 
LinkedList createLinkedList(LinkedList list, int (* cmp) (void*, void*));

void releaseLinkedList(LinkedList list);

void clearLinkedList(LinkedList list);

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

## stack (implemented by array)

int isEmptyStack(Stack stack);

int isFullStack(Stack stack);

Stack createStack(int capacity);

void pushStack(void* value, Stack stack);

void* popStack(Stack stack);

## stack (implemented by linked-list)

Stack* initStack(Stack* stack);

void pushStack(void* value, Stack* stack);

void* popStack (Stack* stack);

int  isEmptyStack(Stack* stack);

void releaseStack(Stack* stack);

