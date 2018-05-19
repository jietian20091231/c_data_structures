#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef struct node {
    int element;
    struct node* left;
    struct node* right;
    int height;
} AvlNode, *AvlTree;

int getHeight(AvlNode* node);

AvlNode* createNode(int key, AvlNode* left, AvlNode* right);

AvlNode* findMaxNode(AvlTree tree);

AvlNode* findMinNode(AvlTree tree);

AvlTree  insertNode(AvlTree tree, int key);

AvlTree  deleteNode(AvlTree tree, int key);

void inOrderTraversal(AvlTree tree);

void printAvlTree(AvlTree tree, int key, int direction);

AvlNode* searchNode(AvlTree tree, int key);



#endif // !_AVL_TREE_H_