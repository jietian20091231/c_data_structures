#include "avlTree.h"
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT(node) ((NULL == node) ? 0 :((AvlNode*)(node) -> height))
#define MAX(a, b)   ((a) > (b) ? (a) : (b))

static AvlTree LLRotation(AvlTree tree);
static AvlTree LRRotation(AvlTree tree);
static AvlTree RRRotation(AvlTree tree);
static AvlTree RLRotation(AvlTree tree);

int getHeight(AvlNode* node)
{
    return HEIGHT(node);
}

AvlNode* createNode(int key, AvlNode* left, AvlNode* right)
{
    AvlNode* node = (AvlNode*)malloc(sizeof(AvlNode));
    if(NULL == node)
    {
        printf("Error, Memory is Out!\n");
        return NULL;
    }

    node -> element = key;
    node -> left = left;
    node -> right = right;
    node -> height = 0;

    return node;
}

AvlNode* findMaxNode(AvlTree tree)
{
    if(NULL == tree) return NULL;
    while(tree -> right)
        tree = tree -> right;
    
    return tree;
}

AvlNode* findMinNode(AvlTree tree)
{
    if(NULL == tree) return NULL;
    while(tree -> left)
        tree = tree -> left;

    return tree;
}

AvlTree  insertNode(AvlTree tree, int key)
{
    if(NULL == tree)
    {
        printf("NULL == tree\n");
        AvlNode *node = createNode(key, NULL, NULL);
        tree = node;
    }
    else if( key < tree -> element)
    {
        printf("key < tree -> elemenet\n");
        tree -> left = insertNode(tree -> left, key);
        if(HEIGHT(tree -> left) - HEIGHT(tree -> right) == 2)
        {
            tree = (key < tree -> left -> element)? LLRotation(tree) : LRRotation(tree);
        }
    }
    else if( key > tree -> element)
    {
        printf("key > tree - > element\n");
        tree -> right = insertNode(tree -> right, key);
        if(getHeight(tree ->right) - getHeight(tree -> left) == 2)
        {
            tree = (key > tree -> right -> element) ? RRRotation(tree) : RLRotation(tree);
        }

    }
    else
    {
        printf("Warning, Can't input same node!\n");
    }

    tree -> height = MAX(getHeight(tree -> left), getHeight(tree -> right)) + 1;

    return tree;
}

AvlTree  deleteNode(AvlTree tree, int key)
{
    return NULL;
}

void inOrderTraversal(AvlTree tree)
{
    if(tree)
    {
        inOrderTraversal(tree -> left);
        printf("%d  ", tree -> element);
        inOrderTraversal(tree -> right);
    }
}

void printAvlTree(AvlTree tree, int key, int direction)
{
    if(tree)
    {
        if(direction == 0) printf("%2d is root\n", tree -> element, key);
        else printf("%2d is %2d's %6s child\n", tree ->element, key, direction == 1? "right": "left");

        printAvlTree(tree -> left, tree -> element, -1);
        printAvlTree(tree -> right, tree -> element, 1);
    }
}

AvlNode* searchNode(AvlTree tree, int key)
{
    if(NULL == tree || tree -> element == key)
    {
        return tree;
    }
    else if(key < tree -> element)
    {
        searchNode(tree -> left, key);
    }
    else if(key > tree -> element)
    {
        searchNode(tree -> right, key);
    }
}

static AvlTree LLRotation(AvlTree tree)
{
   AvlNode* k2 = tree -> left;
   tree -> left = k2 -> right;
   k2 -> right = tree;

   tree -> height = MAX(getHeight(tree -> left), getHeight(tree -> right)) + 1;
   k2 -> height = MAX(getHeight(k2 -> left), getHeight(k2 -> right)) + 1;

   return k2;
}

static AvlTree RRRotation(AvlTree tree)
{
    AvlNode* k3 = tree -> right;
    tree -> right = tree -> left;
    k3 -> left = tree;
    tree -> height = MAX(getHeight(tree -> left), getHeight(tree -> right)) + 1;
    k3 -> height = MAX(getHeight(tree -> left), getHeight(tree -> right)) + 1;

    return k3;


}

static AvlTree LRRotation(AvlTree tree)
{
    tree -> left = RRRotation(tree -> left);
    tree = LLRotation(tree);

    return tree;
}

static AvlTree RLRotation(AvlTree tree)
{
    tree -> right = LLRotation(tree -> right);
    tree = RRRotation(tree);

    return tree;
}
