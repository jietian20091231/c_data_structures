#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

static Node* create_bstree_node(int key, Node* father, Node* left, Node* right);
static Node* bstree_insert(BSTree t, Node* n);

void preorder_bstree(BSTree t)
{
    if(NULL != t)
    {
        printf("%d ", t -> key);
        preorder_bstree(t -> left);
        preorder_bstree(t -> right);
    }
}


void inorder_bstree(BSTree t)
{
    if(NULL != t)
    {
        inorder_bstree(t -> left);
        printf("%d ", t -> key);
        inorder_bstree(t -> right);
    }
}


void postorder_bstree(BSTree t)
{
    if(NULL != t)
    {
        postorder_bstree(t -> left);
        postorder_bstree(t -> right);
        printf("%d ", t -> key);
    }
}


Node* bstree_search(BSTree t, int key)
{
    if(NULL == t || t -> key == key)
    {
        return t;
    }

    if(t -> key < key)
    {
        return bstree_search(t -> left, key);
    }
    else if(t -> key > key)
    {
        return bstree_search(t -> right, key);
    }

}


Node* iterative_bstree_search(BSTree t, int key)
{
    while((NULL != t) && ( t-> key != key))
    {
        if(t -> key > key)
        {
            t = t -> left;
        }
        else if(t -> key < key)
        {
            t = t -> right;
        }
    }

    return t;
}


Node* bstree_minimum(BSTree tree)
{
    if(NULL == tree) return NULL;
    
    Node* result = tree;
    while( result -> left != NULL)
        result = result -> left;

    return result;

}


Node* bstree_maximum(BSTree tree)
{
    if(NULL == tree) return NULL;
    
    Node* result = tree;
    while(result -> right != NULL)
    {
        result = result -> right;
    }
        
    return result;
}


Node* bstree_successor(Node* n)
{
    return NULL;
}


Node* bstree_precursor(Node* x)
{    
    if(x -> left)
        return bstree_maximum(x -> left);
    
    Node* y = x -> father;
    while((y != NULL) && (x != y -> right))
    {
        x = y;
        y = y -> father;
    }

    return y;
}


Node* insert_bstree(BSTree t, int key)
{
    Node* n = NULL;
    if(NULL == (n = create_bstree_node(key, NULL, NULL, NULL))) return NULL;

    return bstree_insert(t, n);
}


Node* delete_bstree(BSTree t, int key)
{
    return NULL;
}


void destroy_bstree(BSTree t)
{
    if(NULL != t)
    {
        destroy_bstree(t -> left);
        destroy_bstree(t -> right);
        free(t);
    }
}


void print_bstree(BSTree t, int key, int direction)
{
    if(NULL != t)
    {
        if( 0 == direction)
        {
            if( t -> left == NULL && t -> right == NULL)
            {
                printf("%2d is root, has not precursor, has not successor(root is a single node).\n", key);
            }
            else
            {
                Node* p = bstree_precursor(t);
                if(p != NULL)
                    printf("%2d is root, has a precursor Node[%d]\n", t -> key, p -> key);
                else
                    printf("%2d is root, has not precurosr.\n", t -> key);
            }
            
            
        }
        else
        {
            Node* p = bstree_precursor(t);
            if(p != NULL)
                printf("%2d is %2d's %s child, has a precursor Node[%d]\n", t -> key, key, (direction == 1) ? "left" : "right", p -> key);
            else
                printf("%2d is %2d's %s child.\n", t -> key, key, (direction == 1) ? "left" : "right");
        }

        print_bstree(t -> left, t -> key, 1);
        print_bstree(t -> right, t -> key, 2);
    }

}

static Node* create_bstree_node(int key, Node* father, Node* left, Node* right)
{
    Node* p = (Node*) malloc(sizeof(struct _node));
    if(NULL == p) return p;

    p -> key = key;
    p -> father = father;
    p -> left = left;
    p -> right = right;

    return p;

}

static Node* bstree_insert(BSTree t, Node* n)
{
    Node* y = NULL;
    Node* x = t;

    while(x != NULL)
    {
        y = x;

        if(n -> key < x -> key)
        {
            x = x -> left;
        }
        else if(n -> key > x -> key)
        {
            x = x -> right;
        }
    }

    n -> father = y;
    if(NULL == y)
    {
        t = n;
    }
    else if(n -> key < y -> key)
    {
        y -> left = n;
    }
    else if(n ->key > y -> key)
    {
        y -> right = n;
    }

    return t;

}
