#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

static Node* create_bstree_node(int key, Node* father, Node* left, Node* right);
static Node* bstree_insert(BSTree t, Node* n);
static Node* bstree_delete(BSTree t, Node* n);
static void printInfo(Node* n, int key, int direction);

const char* root_format = "%2d is root";
const char* node_type_format = "the type of node is %s";
const char* precursor_format = "precursor %2d";
const char* successor_format = "successor %2d";
const char* child_format = "%2d is %2d's %s child";

const char* NODE_TYPE[5] = { "NULL", "SINGLE", "ROOT", "FATHER", "LEAF"};


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
    if( NULL != t)
    {
        if(t -> key > key)
            return bstree_search(t -> left, key);
        else if(t -> key < key )
            return bstree_search(t -> right, key);
        else 
            return t;
    }
    
    return NULL;

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
    if(n -> right) 
        return bstree_minimum(n -> right);
    
    Node* y = n -> father;
    while((y != NULL) && (n != y -> left))
    {
        n = y;
        y = y -> father;
    }

    return y;
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
    Node* n = bstree_search(t, key);

    if(NULL == n ) return t;

    return bstree_delete(t, n);
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
        printInfo(t, key, direction);

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

static Node* bstree_delete(BSTree t, Node* n)
{   
    int type = get_node_type(n);
    if(0 == type) return NULL;
    if(1 == type)
    {
        free(n);
        return NULL;
    }

    if(4 == type)
    {
        if(n -> father -> left == n)
            n -> father -> left = NULL;
        else
           n -> father -> right = NULL;
        
        free(n);
    }
    else
    {
        if(2 == type)
        {
            if(NULL != n -> left && NULL == n -> right)
            {
                Node* p = bstree_precursor(n);
                n -> key = p -> key;
                if(4 == get_node_type(p))
                {
                    p -> father -> right = NULL;
                }
                else
                {
                    p -> father -> right = p -> left;
                    p -> left -> father = p -> father;
                }
                free(p);
            }
            else
            {
                Node* s = bstree_successor(n);
                n -> key = s -> key;
                if(4 == get_node_type(s))
                {
                    s -> father -> left = NULL;
                }
                else
                {
                    s -> father -> left = s -> right;
                    s -> right -> father = s -> father;
                }
                free(s);
            }
        }
        else
        {
            if(NULL != n -> left && NULL == n -> right)
            {
                if(n -> father -> left == n)
                    n -> father -> left = n -> left;
                else
                    n -> father -> right = n -> left;
                
                n -> left -> father = n -> father;

                free(n);
            }
            else
            {
                Node* s = bstree_successor(n);
                n -> key = s -> key;
                if(4 == get_node_type(s))
                {
                    s -> father -> left = NULL;
                }
                else
                {
                    s -> father -> left = s -> right;
                    s -> right -> father = s -> father;
                }

                free(s);
            }
        }

    }

    return t;
    
}

int get_node_type(Node* n)
{
    int type = 0;
    if(NULL != n)
    {
        if(NULL == n -> father)
        {
            if(NULL == n -> left && NULL == n -> right)
                type = 1;
            else
                type = 2;
        }
        else
        {
            if(NULL == n -> left && NULL == n -> right)
                type = 4;
            else 
                type = 3;
        }
    }

    return type;
}

static void printInfo(Node* n, int key, int direction)
{
    int type = get_node_type(n);
    if(0 == type)
    {
        printf("tree is nothing.\n");
        return;
    }

    if(1 == type)
    {
        printf("%d is a single node.\n", n -> key);
        return;
    }

    Node* p = bstree_precursor(n);
    Node* s = bstree_successor(n);


    char buffer[255];
    if(2 == type)
    {
        char format[150];
        strcpy(format, root_format);
        strcat(format, ", ");
        strcat(format, node_type_format);

        if(NULL != p && NULL != s)
        {
            strcat(format, ", ");
            strcat(format, precursor_format);
            strcat(format, ", ");
            strcat(format, successor_format);

            sprintf(buffer, format, key, NODE_TYPE[type], p -> key, s -> key);
            printf("%s.\n", buffer);
        }
        else if(NULL != p && NULL == s)
        {
            strcat(format, ", ");
            strcat(format, precursor_format);

            sprintf(buffer, format, key, NODE_TYPE[type], p -> key);
            printf("%s.\n", buffer);            
        }
        else
        {
            strcat(format, ", ");
            strcat(format, successor_format);

            sprintf(buffer, format, key, NODE_TYPE[type], s -> key);
            printf("%s.\n", buffer);                        
        }

    }
    else
    {
        char format[150];
        strcpy(format, child_format);
        strcat(format, ", ");

        strcat(format, node_type_format);

        char* left_right = "";
        if(1 == direction) 
            left_right = "left";
        else 
            left_right = "right";

        if(NULL != p && NULL != s)
        {
            strcat(format, ", ");
            strcat(format, precursor_format);
            strcat(format, ", ");
            strcat(format, successor_format);

            sprintf(buffer, format, n -> key, key, left_right, NODE_TYPE[type], p -> key, s -> key);
            printf("%s.\n", buffer);
        }
        else if(NULL != p && NULL == s)
        {
            strcat(format, ", ");
            strcat(format, precursor_format);

            sprintf(buffer, format, n -> key, key, left_right, NODE_TYPE[type], p -> key);
            printf("%s.\n", buffer);            
        }
        else
        {
            strcat(format, ", ");
            strcat(format, successor_format);

            sprintf(buffer, format, n -> key, key, left_right, NODE_TYPE[type], s -> key);
            printf("%s.\n", buffer);                        
        }        
    }

}
