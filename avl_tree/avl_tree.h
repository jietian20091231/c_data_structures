#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef struct _node {
    int key;
    int height;
    struct _node * left;
    struct _node * right;
    struct _node * father;
} Node, *AvlTree;

void preorder_avltree(AvlTree t);
void inorder_avltree(AvlTree t);
void postorder_avltree(AvlTree t);

Node* bstree_search(AvlTree t, int key);
Node* iterative_avltree_search(AvlTree t, int key);

Node* bstree_minimum(AvlTree tree);
Node* bstree_maximum(AvlTree tree);

Node* bstree_precursor(Node* n);
Node* bstree_successor(Node* n);

Node* insert_avltree(AvlTree t, int key);
Node* delete_avltree(AvlTree t, int key);

void destroy_avltree(AvlTree t);

void print_avltree(AvlTree t, int key, int direction);

int get_node_type(Node* n);

int get_node_height(Node* n);
int get_node_deepth(Node* n);


#endif