#include "bst.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX( a, b )  ( (a) >= (b) ? (a) : (b) )

void makeEmpty(SearchTree t)
{
    if( NULL != t )
    {
        makeEmpty(t -> left);
        makeEmpty(t -> right);
        free(t);
    }

}


Position find(int key, SearchTree t)
{
    if(NULL == t) return NULL;
    if(t -> key > key)
    {
        return find(key, t -> left);

    } if(t -> key < key)
    {
        return find(key, t -> right);
    }
    else
    {
        return t;
    }
}


Position findMin(SearchTree t)
{
    if(NULL == t) return NULL;

    Position p = t;
    while(p -> left != NULL)
            p = p -> left;
    
    return p;

}


Position findMax(SearchTree t)
{
    if(NULL == t) return NULL;

    Position p = t;
    while(p -> right != NULL)
            p = p -> right;
    
    return p;
}


SearchTree insert(int key, SearchTree t)
{
    if(NULL == t)
    {
        t = (Node*) malloc(sizeof(struct _node));
        if(NULL == t)
        {
            printf("Error, malloc node memory failed!\n");
            exit(-1);
        }

        t -> key = key;
        t -> left = NULL;
        t -> right = NULL;

    }
    else if(t -> key > key)
    {
        t -> left = insert(key, t -> left);
    }
    else if(t -> key < key)
    {
        t -> right = insert(key, t -> right);
    }

    return t;

}


SearchTree delete(int key, SearchTree t)
{

}


void perorder_traversal(SearchTree t)
{
    if(NULL != t )
    {
        printf("%d ", t -> key);
        perorder_traversal(t-> left);
        perorder_traversal(t -> right);
    }

}

void inorder_traversal(SearchTree t)
{
    if(NULL != t)
    {
        inorder_traversal(t -> left);
        printf("%d ", t -> key);
        inorder_traversal(t -> right);
    }

}

void postorder_traversal(SearchTree t)
{
    if(NULL != t)
    {
        postorder_traversal( t -> left );
        postorder_traversal( t -> right );
        printf( "%d ", t -> key );        
    }

}


int getHeight(SearchTree t)
{
    int height = 0;

    if( NULL != t)
    {
        height = MAX( getHeight( t -> left ), getHeight( t -> right ) ) + 1;
    }


    return height;
}

