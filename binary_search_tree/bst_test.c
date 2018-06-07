#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bst.h"

#define MAX 150
#define MIN 1
#define M 1
#define N 10

void buildRandomMat( int (*p)[N], int length);
void testBst(int* p);

int main()
{
    int mat[5][N] = { {0}, {0}, {0}, {0}, {0} };

    buildRandomMat(mat, M);

    int i;
    for(i = 0; i < M; i++)
        testBst(mat[i]);

    return 0;
}

void testBst(int* p)
{
    BSTree bst = NULL;
    int i;

    printf("build Binary Search Tree (BST):\n");
    for( i = 0; i < N; i++)
    {
        printf("%d ", p[i]);
        bst = insert_bstree(bst, p[i]);
    }
        
    
    printf("\ninorder traversal:\n");
    inorder_bstree(bst);

    printf("\nprint BST:\n");
    print_bstree(bst, bst -> key, 0);


    for(i = 0; i < N; i++)
    {
        printf("delete %d\n", p[i]);
        bst = delete_bstree(bst, p[i]);
        if(NULL == bst)
        {
            printf("bstree is none.\n");
            break;
        }
        print_bstree(bst, bst -> key, 0);
    }


    printf("\nDestory bstree.\n");
    destroy_bstree(bst);
}

void buildRandomMat( int (*p)[N], int length)
{
    int index;
    for(index = 0; index < length; index++)
    {
        srand(time(NULL) + index * 1000);
        int randNum;
        int i, j, flag = 0, t = 0;
        while(1)
        {
            flag = 0;
            if(t == N)
                break;
            
            randNum = (rand() % (MAX - MIN)) + MIN;
            for(i = 0; i < t; i++)
            {
                if(p[index][i] == randNum)
                    flag = 1;
            }

            if(flag != 1)
            {
                p[index][t] = randNum;
                t++;
            }
        }

    }
}