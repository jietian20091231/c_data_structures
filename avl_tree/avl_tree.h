#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef struct _node {
    int key;
    int height;
    struct _node * left;
    struct _node * right;
    struct _node * father;
} Node, *AvlTree;

void preorder_avltree( AvlTree t );
void inorder_avltree( AvlTree t );
void postorder_avltree( AvlTree t );

Node* avltree_search( AvlTree t, int key );
Node* iterative_avltree_search( AvlTree t, int key );

Node* avltree_minimum( AvlTree tree );
Node* avltree_maximum( AvlTree tree );

Node* avltree_precursor( Node* n );
Node* avltree_successor( Node* n );

Node* insert_avltree( AvlTree t, int key );
Node* delete_avltree( AvlTree t, int key );

void destroy_avltree( AvlTree t );

int get_node_type( Node* n );

int get_node_height_calc( Node* n );
int get_node_height( Node* n );
int get_node_deepth( Node* n );


#endif
