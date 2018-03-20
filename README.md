# c_data_structures
data_structures (C description)


## double linked list

DuLinkedList createLinked(DuLinkedList list, int (* cmp) (void*, void*));

void releaseLinked(DuLinkedList list);

int isEmptyLinked(DuLinkedList list);

int append(void* value, DuLinkedList list, int mode);

int append_list(DuLinkedList addList, DuLinkedList list, int mode);

int append_array(void* arr[], int length, DuLinkedList list, int mode);

int insert(void* value, Position position, DuLinkedList list, int mode);

int insert_list(DuLinkedList addList, Position position, DuLinkedList list, int mode);

int insert_array(void* arr[], int length, Position position, DuLinkedList list, int mode);

Position find(void* value, DuLinkedList list, int mode);

Position findPrevious(void* value, DuLinkedList list, int mode);

int find_index(void* value, DuLinkedList list);

void* get(Position position);

void* rpop(DuLinkedList list);

void* lpop(DuLinkedList list);

int rpush(void* value, DuLinkedList list);

int lpush(void* value, DuLinkedList list);


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

