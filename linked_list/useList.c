#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(void* value_1, void* value_2);

struct _student {
    char* name;
    int id;
};

typedef struct _student Student;

int main(void)
{
    LinkedList stuList;
    stuList = createLinkedList(stuList, cmp);
    int index;
    for(index = 0 ; index < 5; index++)
    {
        char* name = (char*)calloc(10,sizeof(char));
        memset(name,0,sizeof(char));
        sprintf(name, "name_%d", index);
        printf("%s\n", name);

        Student* stu  = (Student*)malloc(sizeof(Student));
        stu -> id = index;
        stu -> name = name;

        //printf("[%p]%d, %s\n", stu, stu -> id, stu -> name);

        append(stu, stuList);
    }

    Student* stu_array[5];
    for(index = 0; index < 5; index++)
    {
        char* name = (char*)calloc(10, sizeof(char));
        memset(name, 0, sizeof(char));
        sprintf(name, "name_%d", 5 + index);

        Student* stu = (Student*)malloc(sizeof(Student));
        stu -> id = 5 + index;
        stu -> name = name;

        stu_array[index] = stu;
        
    }

    append_array(stu_array,5,stuList);

    printf("list -> data_list = %p\n", stuList -> data_list);
    printf("list -> rear = %p\n", stuList -> rear);

    puts("Read stuList :");
    Position p = stuList -> data_list;
    printf("%p\n", p);
    while(p)
    {
        Student* stu = (Student*) p -> element;
        printf("[%p, %p]%d, %s\n", p, stu, stu -> id, stu -> name);
        p = p -> next;
    }

    p = find(stu_array[2], stuList);
    printf("find p address is %p\n", p);
    if(p)
    {
        Student* stu = (Student*) p ->element;
        printf("[%p, %p]%d, %s\n", p, stu, stu -> id, stu -> name);
    }

    Student* not_found = (Student*) malloc(sizeof(Student));
    not_found -> id = 10;
    not_found -> name = "JamesBond";

    p = find(not_found, stuList);
    if(NULL == p)
    {
        printf("Student'is %d not in the list.\n", not_found -> id);
    }

    p = findPrevious(stu_array[2],stuList);
    if(NULL != p)
    {
        Student* st = (Student*) p -> element;
        printf("Student[%d, %s] 's previous is [%d, %s].\n", 
                stu_array[2] -> id, stu_array[2] -> name,
                st -> id, st -> name
        );
    }

    index = find_index(stu_array[2], stuList);
    if(index > -1 )
    {
        printf("Student is found, student[%d, %s] index is %d\n", stu_array[2] -> id, stu_array[2] -> name, index);
    }
    else
    {
        printf("student is not found.\n");
    }

    p = stuList -> data_list;
    while(p)
    {
        Student* st = (Student*) p ->element;
        printf("Student[%d %s].\n", st -> id, st -> name);
        p = p -> next;
    }

    void* obj;
    while((obj = remove_fifo(stuList)) != NULL)
    {
        Student* stu = (Student*) obj;
        printf("list surplus %d elements, remove student[%d, %s]\n", 
                stuList -> size,
                stu -> id,
                stu -> name
        );

        free(stu -> name);
        free(stu);

        stu = NULL;
        
    }
    

    return 0;
}

int cmp(void* value_1, void* value_2)
{
    Student* stu_1 = (Student*) value_1;
    Student* stu_2 = (Student*) value_2;

    return stu_1 -> id - stu_2 -> id;
}

