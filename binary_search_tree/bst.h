#ifndef _BST_H_
#define _BST_H_

typedef struct _node {
    int key;
    struct _node * left;
    struct _node * right;
    struct _node * father;
} Node, *BSTree;

void preorder_bstree(BSTree t);
void inorder_bstree(BSTree t);
void postorder_bstree(BSTree t);

Node* bstree_search(BSTree t, int key);
Node* iterative_bstree_search(BSTree t, int key);

Node* bstree_minimum(BSTree tree);
Node* bstree_maximum(BSTree tree);

Node* bstree_next(Node* n);
Node* bstree_previous(Node* n);

Node* insert_bstree(BSTree t, int key);
Node* delete_bstree(BSTree t, int key);

void destroy_bstree(BSTree t);

void print_bstree(BSTree t, int key, int direction);


#endif