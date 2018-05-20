#ifndef _BST_H_
#define _BST_H_

struct _node {
    int key;
    struct _node * left;
    struct _node * right;
};


typedef struct _node Node;
typedef Node * Position;
typedef Node * SearchTree;

void makeEmpty(SearchTree t);
Position find(int key, SearchTree t);
Position findMin(SearchTree t);
Position findMax(SearchTree t);
SearchTree insert(int key, SearchTree t);
SearchTree delete(int key, SearchTree t);
int getHeight(SearchTree t);
void perorder_traversal(SearchTree t);
void inorder_traversal(SearchTree t);
void postorder_traversal(SearchTree t);


#endif