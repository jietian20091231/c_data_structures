#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_tree.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static Node* create_avltree_node(int key, Node* father, Node* left, Node* right);
static Node* avltree_insert(AvlTree t, Node* n);
static Node* avltree_delete(AvlTree t, Node* n);
static void  printInfo(Node* n, int key, int direction);
static Node* left_left_rotation(Node* t);
static Node* right_right_rotation(Node* t);

const char* root_format = "%2d is root";
const char* node_type_format = "the type of node is %s";
const char* precursor_format = "precursor %2d";
const char* successor_format = "successor %2d";
const char* child_format = "%2d is %2d's %s child";

const char* NODE_TYPE[5] = { "NULL", "SINGLE", "ROOT", "FATHER", "LEAF"};


void preorder_avltree(AvlTree t)
{
    if(NULL != t)
    {
        printf("%d ", t -> key);
        preorder_avltree(t -> left);
        preorder_avltree(t -> right);
    }
}


void inorder_avltree(AvlTree t)
{
    if(NULL != t)
    {
        inorder_avltree(t -> left);
        printf("%d ", t -> key);
        inorder_avltree(t -> right);
    }
}


void postorder_avltree(AvlTree t)
{
    if(NULL != t)
    {
        postorder_avltree(t -> left);
        postorder_avltree(t -> right);
        printf("%d ", t -> key);
    }
}


Node* avltree_search(AvlTree t, int key)
{
    if( NULL != t)
    {
        if(t -> key > key)
            return avltree_search(t -> left, key);
        else if(t -> key < key)
            return avltree_search(t -> right, key);
        else
            return t;
    }
    
    return NULL;

}


Node* iterative_avltree_search(AvlTree t, int key)
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


Node* avltree_minimum(AvlTree tree)
{
    if(NULL == tree) return NULL;
    
    Node* result = tree;
    while( result -> left != NULL)
        result = result -> left;

    return result;

}


Node* avltree_maximum(AvlTree tree)
{
    if(NULL == tree) return NULL;
    
    Node* result = tree;
    while(result -> right != NULL)
    {
        result = result -> right;
    }
        
    return result;
}


Node* avltree_successor(Node* n)
{
    if(n -> right) 
        return avltree_minimum(n -> right);
    
    Node* y = n -> father;
    while((y != NULL) && (n != y -> left))
    {
        n = y;
        y = y -> father;
    }

    return y;
}


Node* avltree_precursor(Node* x)
{    
    if(x -> left)
        return avltree_maximum(x -> left);
    
    Node* y = x -> father;
    while((y != NULL) && (x != y -> right))
    {
        x = y;
        y = y -> father;
    }

    return y;
}


Node* insert_avltree(AvlTree t, int key)
{
    Node* n = NULL;
    if(NULL == (n = create_avltree_node(key, NULL, NULL, NULL))) return NULL;

    return avltree_insert(t, n);
}


Node* delete_avltree(AvlTree t, int key)
{
    Node* n = avltree_search(t, key);

    if(NULL == n ) return t;

    return avltree_delete(t, n);
}


void destroy_avltree(AvlTree t)
{
    if(NULL != t)
    {
        destroy_avltree(t -> left);
        destroy_avltree(t -> right);
        free(t);
    }
}


void print_avltree(AvlTree t, int key, int direction)
{
    if(NULL != t)
    {
        printInfo(t, key, direction);

        print_avltree(t -> left, t -> key, 1);
        print_avltree(t -> right, t -> key, 2);
    }

}

static Node* create_avltree_node(int key, Node* father, Node* left, Node* right)
{
    Node* p = (Node*) malloc(sizeof(struct _node));
    if(NULL == p) return p;

    p -> key = key;
    p -> father = father;
    p -> left = left;
    p -> right = right;

    return p;

}

static Node* avltree_insert(AvlTree t, Node* n)
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

static Node* avltree_delete(AvlTree t, Node* n)
{

    return NULL;
}


int get_node_height(Node* n)
{
    if(NULL == n ) return -1;
    return n -> height;
}

int get_node_height_calc(Node* n)
{
    int type = get_node_type(n);
    if(0 == n) return -1;
    if(1 == n) return 0;

    int height = 0;
    if(NULL != n)
    {
        int left = get_node_height_calc(n -> left);
        int right = get_node_height_calc(n -> right);
        height = (left >= right) ? left + 1 : right + 1;
    }

    return height;
}


int get_node_deepth(Node* n)
{
    int type = get_node_type(n);
    if(0 == type) return -1;
    if(1 == type) return 0;

    Node* temp = n;
    int depth = 0;
    while(n -> father != NULL)
    {
        depth++;
        n = n -> father;
    }

    return depth;
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

    Node* p = avltree_precursor(n);
    Node* s = avltree_successor(n);


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

/*
  This function can be called only if k2 has a left child
  Perform a rotate between a node (K2) and its left child
  Update heights, then return new root.
 */
static Node* left_left_rotation(Node* k2)
{
    Node* k1;

    //node changed
    k1 = k2 -> left;
    k2 -> left = k1 -> right;
    k1 -> right = k2;

    //father changed

    Node* k2_father = k2 -> father;
    if(NULL != k2_father)
    {
        if(k2_father -> left == k2)
            k2 -> father -> left = k1;
        else
            k2 -> father -> right = k1;
    }
    k1 -> father = k2_father;

    // TO DO : update node's father.


    //height updated
    k2 -> height = MAX(get_node_height(k2 -> left), get_node_height(k2 -> right)) + 1;
    k1 -> height = MAX(get_node_height(k1 -> left), get_node_height(k1 ->right)) + 1;

    return k1;
}

static Node* right_right_rotation(Node* k1)
{
    Node* k2;

    //node changed
    k2 = k1 -> right;
    k1 -> right = k2 -> left;
    k2 -> left = k1;

    //father changed
    // TO DO : update node's father.

    //height updated
    k1 -> height = MAX(get_node_height(k1 ->left), get_node_height(k1 -> right)) + 1;
    k2 -> height = MAX(get_node_height(k2 ->left), get_node_height(k2 -> right)) + 1;


    return k2;
}
