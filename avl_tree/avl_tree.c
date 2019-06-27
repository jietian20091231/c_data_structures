#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_tree.h"

#define MAX( a, b ) ( ( a ) > ( b ) ? ( a ) : ( b ) )

static Node* create_avltree_node( int key, Node* father, Node* left, Node* right );
static Node* avltree_insert( AvlTree t, Node* n );
static Node* avltree_delete( AvlTree t, Node* n );
static void  printInfo( Node* n, int key, int direction );
static Node* left_rotation( Node* t );     //ll
static Node* right_rotation( Node* t );   //rr
static Node* left_right_rotation( Node* t );    //lr
static Node* right_left_rotation( Node* t);     //rl

static Node* bstree_insert( AvlTree t, Node* n );

static Node* lost_balance_node( Node * t );

static int check_node_type( Node* t );  // 0 NULL, 1 Single, 2, root, 3, left child, 4 right child

const char* root_format = "%2d is root";
const char* node_type_format = "the type of node is %s";
const char* precursor_format = "precursor %2d";
const char* successor_format = "successor %2d";
const char* child_format = "%2d is %2d's %s child";

const char* NODE_TYPE[ 5 ] = { "NULL", "SINGLE", "ROOT", "TRUNK", "LEAF" };


void preorder_avltree( AvlTree t )
{
    if ( NULL != t ) {
        printf( "%d " , t -> key );
        preorder_avltree( t -> left );
        preorder_avltree( t -> right );
    }
}


void inorder_avltree( AvlTree t )
{
    if ( NULL != t ) {
        inorder_avltree( t -> left );
        printf( "%d ", t -> key );
        inorder_avltree( t -> right );
    }
}


void postorder_avltree( AvlTree t )
{
    if ( NULL != t ) {
        postorder_avltree( t -> left );
        postorder_avltree( t -> right );
        printf( "%d ", t -> key );
    }
}


Node* avltree_search( AvlTree t, int key )
{
    if ( NULL != t ) {
        if( t -> key > key )
            return avltree_search( t -> left, key );
        else if(t -> key < key)
            return avltree_search( t -> right, key );
        else
            return t;
    }

    return NULL;

}


Node* iterative_avltree_search( AvlTree t, int key )
{
    while ( ( NULL != t ) && ( t-> key != key ) ) {
        if( t -> key > key ) {
            t = t -> left;
        } else if( t -> key < key ) {
            t = t -> right;
        }
    }

    return t;
}


Node* avltree_minimum( AvlTree tree )
{
    if ( NULL == tree ) return NULL;

    Node* result = tree;
    while( result -> left != NULL )
        result = result -> left;

    return result;

}


Node* avltree_maximum( AvlTree tree )
{
    if( NULL == tree ) return NULL;

    Node* result = tree;
    while( result -> right != NULL )
        result = result -> right;

    return result;
}


Node* avltree_successor( Node* n )
{
    if( n -> right )
        return avltree_minimum( n -> right );

    Node* y = n -> father;
    while( ( y != NULL ) && ( n != y -> left ) ) {
        n = y;
        y = y -> father;
    }

    return y;
}


Node* avltree_precursor( Node* n )
{
    if( n -> left )
        return avltree_maximum( n -> left );

    Node* y = n -> father;
    while( ( y != NULL ) && ( n != y -> right)) {
        n = y;
        y = y -> father;
    }

    return y;
}


Node* insert_avltree( AvlTree t, int key )
{
    Node* n = NULL;
    if( NULL == ( n = create_avltree_node( key, NULL, NULL, NULL ) ) ) return NULL;

    printf( "n -> key = %d\n", n -> key );
    return avltree_insert( t, n );
}


Node* delete_avltree( AvlTree t, int key )
{
    return NULL;
}


void destroy_avltree( AvlTree t )
{
    if ( NULL != t ) {

        destroy_avltree( t -> left );
        destroy_avltree( t -> right );
        free( t );
    }
}


void print_avltree( AvlTree t, int key, int direction )
{
    if ( NULL != t ) {

        printInfo( t, key, direction );

        print_avltree( t -> left, t -> key, 1 );
        print_avltree( t -> right, t -> key, 2 );
    }

}

static Node* create_avltree_node( int key, Node* father, Node* left, Node* right ) {
    Node* p = ( Node* ) malloc( sizeof( struct _node ) );
    if( NULL == p ) return p;

    p -> key = key;
    p -> father = father;
    p -> left = left;
    p -> right = right;

    return p;
}


static Node* avltree_insert( AvlTree t, Node * n )
{
    t = bstree_insert( t, n );
    printf( "[avltree_insert, bstree_insert]\n" );
    print_avltree( t, t -> key, 0 );

    printf( "[avltree_insert] get_node_height( t -> left ) = %d\n", get_node_height( t -> left ) );
    printf( "[avltree_insert] get_node_height( t -> right ) = %d\n", get_node_height( t -> right ) );
    printf( "[avltree_insert] t = %p, t -> key = %d\n", t, t -> key );

    Node* k1 = lost_balance_node( n );
    if ( k1 == NULL ) return t;

    if( k1 != NULL ) {
        printf( "====================> k1 -> key  = %d\n", k1 -> key );
        printf( "====================> get_node_height( k1 -> left  ) = %d\n", get_node_height( k1 -> left  ) );
        printf( "====================> get_node_height( k1 -> right  ) = %d\n", get_node_height( k1 -> right  ) );
        if( get_node_height( k1 -> left  ) > get_node_height( k1 -> right) ) {
                printf( "====================> get_node_height( k1 -> left -> right ) = %d\n", get_node_height( k1 -> left -> right ) );
                printf( "====================> get_node_height( k1 -> right ) = %d\n", get_node_height( k1 -> right ) );
                if ( get_node_height( k1 -> left -> right ) == get_node_height( k1 -> right ) ) {
                    printf( "[avltree_insert singel left rotation]\n" );
                    k1 = right_rotation( k1 );
                    if ( NULL == k1 -> father ) t = k1; //change root node
                } else {
                    printf( "[avltree_insert left right rotation]\n" );
                    k1 = left_right_rotation( k1 );
                    if ( NULL == k1 -> father ) t = k1;
                }

        } else if ( get_node_height( k1 -> left  ) < get_node_height( k1 -> right) ) {
                printf( "====================> get_node_height( k1 -> right -> left ) = %d\n", get_node_height( k1 -> right -> left ) );
                printf( "====================> get_node_height( k1 -> left ) = %d\n", get_node_height( k1 -> left ) );
                if ( get_node_height( k1 -> right -> left ) == get_node_height( k1 -> left ) ) {
                    printf( "[avltree_insert singel right rotation]\n" );
                    k1 = left_rotation( k1 );
                    if ( NULL == k1 -> father ) t = k1; //change root node
                } else {
                    printf( "[avltree_insert right left rotation]\n" );
                    k1 = right_left_rotation( k1 );
                    if ( NULL == k1 -> father ) t = k1;
                }
        }
    }


    return t;
}

/*
static Node* avltree_insert( AvlTree t, Node* n )
{
    t = bstree_insert( t, n );
    printf( "[avltree_insert, bstree_insert]\n" );
    print_avltree( t, t -> key, 0 );

    printf( "[avltree_insert] get_node_height( t -> left ) = %d\n", get_node_height( t -> left ) );
    printf( "[avltree_insert] get_node_height( t -> left ) = %d\n", get_node_height( t -> right ) );
    printf( "[avltree_insert] t = %p, t -> key = %d\n", t, t -> key );

    if ( t != NULL ) {
        if( get_node_height( t -> left ) - get_node_height( t -> right ) == -2 ) {
            //left rotation
            Node* k1 = lost_balance_node( n );
            printf( "[avltree_insert left case] k1 -> key = %d\n", k1 -> key );
            printf( "[avltree_insert left case] k1 -> right  = %p\n", k1 -> right );
            if ( get_node_height( k1 -> right -> left ) == 0 ) {
                printf( "[avltree_insert singel left rotation]\n" );
                k1 = left_rotation( k1 );
                if ( NULL == k1 -> father ) t = k1; //change root node
            } else {
                printf( "[avltree_insert singel right left rotation]\n" );
                k1 = right_left_rotation( k1 );
                if ( NULL == k1 -> father ) t = k1;
            }


        } else if( get_node_height( t -> left ) - get_node_height( t -> right ) == 2 ) {
            //right_rotation
            Node* k1 = lost_balance_node( n );
            printf( "[avltree_insert right case] k1 -> key = %d\n", k1 -> key );
            if ( get_node_height( t -> right )  == 0 ) {
                printf( "[avltree_insert singel right rotation]\n" );
                k1 = right_rotation( k1 );
                if ( NULL == k1 -> father ) t = k1; //change root node
            } else {
                printf( "[avltree_insert singel left right rotation]\n" );
                k1 = left_right_rotation( k1 );
                if ( NULL == k1 -> father ) t = k1;
            }
        }
    }

    return t;
}
 */


static Node* avltree_delete( AvlTree t, Node* n )
{
    return NULL;
}



int get_node_height( Node* t ) {
    int tree_deepth;
    int left_deepth;
    int right_deepth;

    if( NULL == t ) {
        tree_deepth = 0;
        return tree_deepth;
    }

    left_deepth = get_node_height( t -> left );
    right_deepth = get_node_height( t -> right );

    tree_deepth = 1 + ( left_deepth > right_deepth ? left_deepth : right_deepth );

    return tree_deepth;
}


int get_node_deepth( Node* n )
{
    int type = get_node_type( n );
    if( 0 == type ) return -1;
    if( 1 == type ) return 0;

    Node* temp = n;
    int depth = 0;
    while( n -> father != NULL ) {
        depth++;
        n = n -> father;
    }

    return depth;
}


int get_node_type( Node* n )
{
    int type = 0;
    if( NULL != n )  {
        if( NULL == n -> father ) {
            if( NULL == n -> left && NULL == n -> right )
                type = 1;
            else
                type = 2;
        } else {
            if( NULL == n -> left && NULL == n -> right )
                type = 4;
            else
                type = 3;
        }
    }

    return type;
}

static void printInfo( Node* n, int key, int direction )
{
    int type = get_node_type( n );
    if( 0 == type ) {
        printf( "tree is nothing.\n" );
        return;
    }

    if( 1 == type ) {
        printf( "%d is a single node.\n", n -> key );
        return;
    }

    Node* p = avltree_precursor( n );
    Node* s = avltree_successor( n );


    char buffer[ 255 ];
    if( 2 == type ) {
        char format[ 150 ];
        strcpy( format, root_format );
        strcat( format, ", " );
        strcat( format, node_type_format );

        if( NULL != p && NULL != s ) {
            strcat( format, ", " );
            strcat( format, precursor_format );
            strcat( format, ", " );
            strcat( format, successor_format );

            sprintf( buffer, format, key, NODE_TYPE[ type ], p -> key, s -> key );
            printf( "%s.\n", buffer );

        } else if( NULL != p && NULL == s ) {

            strcat( format, ", " );
            strcat( format, precursor_format );

            sprintf( buffer, format, key, NODE_TYPE[ type ], p -> key );
            printf( "%s.\n", buffer );
        }
        else {
            strcat( format, ", " );
            strcat( format, successor_format );

            sprintf( buffer, format, key, NODE_TYPE[ type ], s -> key );
            printf( "%s.\n", buffer );
        }

    } else {
        char format[ 150 ];
        strcpy( format, child_format );
        strcat( format, ", " );

        strcat( format, node_type_format );

        char* left_right = "";
        if( 1 == direction )
            left_right = "left";
        else
            left_right = "right";

        if( NULL != p && NULL != s ) {
            strcat( format, ", " );
            strcat( format, precursor_format );
            strcat( format, ", " );
            strcat( format, successor_format );

            sprintf( buffer, format, n -> key, key, left_right, NODE_TYPE[ type ], p -> key, s -> key );
            printf( "%s.\n", buffer );

        } else if( NULL != p && NULL == s ) {
            strcat( format, ", " );
            strcat( format, precursor_format );

            sprintf( buffer, format, n -> key, key, left_right, NODE_TYPE[type], p -> key );
            printf( "%s.\n", buffer );
        } else {
            strcat( format, ", " );
            strcat( format, successor_format );

            sprintf( buffer, format, n -> key, key, left_right, NODE_TYPE[ type ], s -> key );
            printf( "%s.\n", buffer );
        }
    }
}


static Node* left_rotation( Node* k1 )
{
    Node* ret = NULL;
    int type = check_node_type( k1 );
    printf( "[left_rotation] get_node_height( k1 -> right ) = %d, get_node_height( k1 -> left ) = %d\n", get_node_height( k1 -> left ), get_node_height( k1 -> right ) );
    printf( "[left_rotation] get_node_height( k1 -> right ) - get_node_height( k1 -> left ) = %d\n", get_node_height( k1 -> right ) - get_node_height( k1 -> left ) );
    if ( 2 == get_node_height( k1 -> right ) - get_node_height( k1 -> left ) ) {
        Node* k2 = k1 -> right;
        if ( 0 == get_node_height( k1 -> left ) && 0 == get_node_height( k2 -> left ) ) {
            k2 -> father = k1 -> father;
            k1 -> right = NULL;
            k2 -> left = k1;
            k1 -> father = k2;

        } else if ( 1 == get_node_height( k1 -> left ) && 1 == get_node_height( k2 -> left ) ) {
            Node* k3 = k2 -> left;
            k2 -> father = k1 -> father;
            k2 -> left = k1;
            k1 -> father = k2;
            k1 -> right = k3;
            k3 -> father = k1;
        } else if ( 1 == get_node_height( k1 -> left ) && 0 == get_node_height( k2 -> left ) ) {
            printf( "<=======================>\n" );
            k2 -> father = k1 -> father;
            k1 -> right = NULL;
            k2 -> left = k1;
            k1 -> father = k2;
        }

        if ( 3 == type ) {
            k2 -> father -> left = k2;
        } else if ( 4 == type ) {
            k2 -> father -> right = k2;
        }

        ret = k2;
        printf( "[left_rotation]\n");
        print_avltree( ret, ret -> key, 0 );
        printf( "\n" );

    } else {

        Node* k2 = k1 -> right;
        printf( "[left_right_rotation, left_rotation] k2 -> left = %p\n", k2 -> left );
        int k1_has_left = ( k1 -> left ) ? 1 : 0;

        printf( "[left_right_rotation, left_rotation] k1_has_left = %d\n", k1_has_left );
        printf( "[left_right_rotation, left_rotation] k1 -> key = %d, k1 address = %p\n", k1 -> key, k1 );
        printf( "[left_right_rotation, left_rotation] k2 -> key = %d, k2 address = %p\n", k2 -> key, k2 );

        Node* k3 = k2 -> left;
        int stat = check_node_type( k3 );
        printf( "[left_right_rotation, left_rotation] stat = %d\n", stat );
        k2 -> father = k1 -> father;
        k2 -> left = k1;
        k1 -> father = k2;

        if ( k1_has_left ) {
            k1 -> right = NULL;
        } else {
            k1 -> left = k1 -> right = NULL;
        }

        if ( 3 == stat )
        {
            k1->right = k3;
            k3->father = k1;
        }

        ret = k2;
        printf( "[left_right_rotation, left_rotation] ret -> left = %p\n", ret -> left );
        if( k2 -> left ) {
            printf( "[left_right_rotation, left_rotation] k2 -> left -> key = %d\n", k2 -> left -> key );
        }
        printf( "[left_right_rotation, left_rotation] ret -> key = %d( %p )\n", ret -> key, ret );
        printf( "[left_right_rotation, left_rotation]\n");
        print_avltree( ret, ret -> key, 0 );
        printf( "\n" );

    }

    return ret;
}


static Node* right_rotation( Node* k1 )
{
    Node* ret = NULL;
    int type = check_node_type( k1 );
    printf( "[right_rotation] get_node_height( k1 -> right ) = %d, get_node_height( k1 -> left ) = %d\n", get_node_height( k1 -> left ), get_node_height( k1 -> right ) );
    printf( "[right_rotation] get_node_height( k1 -> left ) - get_node_height( k1 -> right ) = %d\n", get_node_height( k1 -> left ) - get_node_height( k1 -> right ) );
    printf( "[right_rotation]  type = %d\n", type );
    if ( 2 == get_node_height( k1 -> left ) - get_node_height( k1 -> right ) ) {
        Node* k2 = k1 -> left;
        printf( "[right_rotation,  singel] k1 -> key = %d, k2 -> key = %d\n", k1 -> key, k2 -> key );
        if ( 0 == get_node_height( k1 -> right ) && 0 == get_node_height( k2 -> right ) ) {
            k2 -> father = k1 -> father;
            k1 -> left = NULL;
            k2 -> right = k1;
            k1 -> father = k2;

        } else if ( 1 == get_node_height( k1 -> right)  &&  1 == get_node_height( k2 -> right) ) {
            Node* k3 = k2 -> right;
            k2 -> father = k1 -> father;
            k2 -> right = k1;
            k1 -> father = k2;
            k1 -> left = k3;
            k3 -> father = k1;
        } else if ( 1 == get_node_height( k1 -> right ) && 0 == get_node_height( k2 -> right ) ) {
            printf( "<=======================>\n" );
            k2 -> father = k1 -> father;
            k1 -> left = NULL;
            k2 -> right = k1;
            k1 -> father = k2;
        }

        if ( 3 == type ) {
            k2 -> father -> left  = k2;
        } else if ( 4 == type ) {
            k2 -> father -> right  = k2;
        }

        ret = k2;
        printf( "[right_rotation]\n");
        print_avltree( ret, ret -> key, 0 );
        printf( "\n" );

    } else {

        Node* k2 = k1 -> left;
        int k1_has_right = ( k1 -> right ) ? 1 : 0;

        printf( "[right_left_rotation, right_rotation] k1_has_right = %d\n", k1_has_right );

        printf( "[right_left_rotation, right_rotation]  k1 -> key = %d, k1 address = %p\n", k1 -> key, k1 );
        printf( "[right_left_rotation, right_rotation]  k2 -> key = %d, k2 address = %p\n", k2 -> key, k2 );

        Node* k3 = k2 -> right;
        int stat = check_node_type( k3 );
        printf( "[right_left_rotation, right_rotation] stat = %d\n", stat );

        k2->father = k1->father;
        k2->right = k1;
        k1->father = k2;

        if ( k1_has_right ) {
            k1 -> left = NULL;
        } else {
            k1 -> left = k1 -> right = NULL;
        }

        if ( 4 == stat )
        {
            k1->left = k3;
            k3->father = k1;
        }

        ret = k2;
        printf( "[right_left_rotation, right_rotation] ret -> key = %d( %p )\n", ret -> key, ret );
        printf( "[right_left_rotation, right_rotation]\n");
        print_avltree( ret, ret -> key, 0 );
        printf( "\n" );
    }

    return ret;
}

static Node* left_right_rotation( Node* t )
{
    t -> left = left_rotation( t -> left );
    printf( "============[left_right_rotation]============\n" );
    print_avltree( t, t -> key, 0 );
    printf( "\n" );

    return right_rotation( t );
}


static Node* right_left_rotation( Node* t)
{
    t -> right = right_rotation( t -> right );
    printf( "============[right_left_rotation]============\n" );
    print_avltree( t, t -> key, 0 );
    printf( "\n" );

    return left_rotation( t );
}


// 0 NULL, 1 Single, 2, root, 3, left child, 4 right child
static int check_node_type( Node* t )
{
    if ( t == NULL ) return 0;

    int type;

    if ( NULL == t -> father ) {
        if ( NULL == t -> left && NULL == t -> right )
            type = 1;
        else
            type = 2;

    } else {
        if ( t ==  t -> father -> left ) {
            type = 3;
        } else if ( t ==  t -> father -> right ) {
            type = 4;
        }
    }

    return type;
}

static Node* bstree_insert(AvlTree t, Node* n)
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


static Node* lost_balance_node( Node * t )
{
    Node* ret = NULL;
    Node* tmp = t;
    do {
        printf( "[lost_balance_node] t -> key = %d( %p )\n", t -> key, t );
        tmp =  tmp -> father;
        if( NULL == tmp ) break;
        printf( "[lost_balance_node] t -> father -> key = %d( %p )\n", t -> father -> key, t -> father );
        int diff = get_node_height( tmp -> left )  - get_node_height( tmp -> right );
        if( abs( diff ) == 2 ) {
            ret = tmp;
            printf( "[lost_balance_node]  found lost blance Node address is %p, value is %d\n", ret , ret -> key );
            break;
        }

    } while( 1 );

    printf( "[lost_balance_node] ret = %p\n", ret );
    return ret;
}
