#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_tree.h"

#define MAX( a, b ) ( ( a ) > ( b ) ? ( a ) : ( b ) )

static Node* create_avltree_node( int key, Node* father, Node* left, Node* right );
static Node* avltree_insert( AvlTree t, Node* n );
static void  printInfo( Node* n, int key, int direction );
static Node* left_rotation( Node* t );     //ll
static Node* right_rotation( Node* t );   //rr
static Node* left_right_rotation( Node* t );    //lr
static Node* right_left_rotation( Node* t);     //rl

static Node* special_left_rotation( Node * t );
static Node* special_right_rotation( Node * t );

static Node* bstree_insert( AvlTree t, Node* n );
static Node* bstree_delete( AvlTree t, Node *n );

static Node *insert_lost_balance_node( Node * t );
static Node *lost_balance_node( Node * t );

static int check_node_type( Node* t );  // 0 NULL, 1 Single, 2, root, 3, left child, 4 right child

static void print_node_info( const char* msg, Node * t );

Node* last_check = NULL;
static void check_whole_tree_blanace( Node* t );

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
    Node* n = avltree_search( t, key );
    if ( NULL == n ) {
        printf( "[delete_avltree] the Node( %d ) is not found!\n", key );
        return t;
    }

    Node* n_successor = avltree_successor( n );
    if( NULL != n_successor ) {
        printf( "[delete_avltree] the Node( %d ) successor is %d( %p )\n", key, n_successor -> key, n_successor );
        print_node_info( "delete_avltree, n_successor" ,n_successor );
    }

    Node* n_father = n -> father;
    if( n_father != NULL ) {
        printf( "[delete_avltree] n_father -> key = %d\n", n_father -> key );
    }

    t = bstree_delete( t, n );
    if( NULL == t ) {
        return t;
    }

    printf( "[delete_avltree, bstree_delete]\n" );
    print_avltree( t, t -> key, 0 );

    Node* k1 = NULL;
    if ( NULL ==  n_successor )
    {
        if ( NULL == n_father ) {
            k1 = lost_balance_node( t );
        } else {
            k1 = lost_balance_node( n_father );
        }
    } else {
        if ( n_father != NULL && 2 == abs( get_node_height( n_father -> left ) - get_node_height( n -> father -> right ) ) ) {
            k1 = n_father;
        } else {
            printf( "[delete_avltree, lost_balance_node] n_successor -> key = %d\n" , n_successor -> key );
            k1 = lost_balance_node( n_successor );
        }

    }

    if ( k1 == NULL ) return t;

    if( k1 != NULL ) {
        printf( "====================> k1 -> key  = %d\n", k1 -> key );
        printf( "====================> get_node_height( k1 -> left  ) = %d\n", get_node_height( k1 -> left  ) );
        printf( "====================> get_node_height( k1 -> right  ) = %d\n", get_node_height( k1 -> right  ) );
        if( get_node_height( k1 -> left  ) > get_node_height( k1 -> right) ) {
                printf( "====================> get_node_height( k1 -> left -> right ) = %d\n", get_node_height( k1 -> left -> right ) );
                printf( "====================> get_node_height( k1 -> right ) = %d\n", get_node_height( k1 -> right ) );
                if ( get_node_height( k1 -> left -> right ) == get_node_height( k1 -> right ) ) {
                    printf( "[delete_avltree single left rotation]\n" );
                    k1 = right_rotation( k1 );
                    if ( NULL == k1 -> father ) t = k1; //change root node
                } else if ( 0 == get_node_height( k1 -> right )
                    && get_node_height( k1 -> left -> left ) == get_node_height( k1 -> left -> right)
                ) {
                    printf( "[delete_avltree, special single right rotation]\n" );
                    k1 = special_right_rotation( k1 );
                    if ( NULL == k1 -> father ) t = k1;

                } else {
                    printf( "[delete_avltree left right rotation]\n" );
                    k1 = left_right_rotation( k1 );
                    if ( NULL == k1 -> father ) t = k1;
                }

        } else if ( get_node_height( k1 -> left  ) < get_node_height( k1 -> right) ) {
                printf( "====================> get_node_height( k1 -> right -> left ) = %d\n", get_node_height( k1 -> right -> left ) );
                printf( "====================> get_node_height( k1 -> left ) = %d\n", get_node_height( k1 -> left ) );
                if ( get_node_height( k1 -> right -> left ) == get_node_height( k1 -> left ) ) {
                    printf( "[delete_avltree single right rotation]\n" );
                    k1 = left_rotation( k1 );
                    if ( NULL == k1 -> father ) t = k1; //change root node
                } else if ( 0 == get_node_height( k1 -> left )
                            && get_node_height( k1 -> right -> left ) == get_node_height( k1 -> right -> right )
                ) {
                    printf( "[delete_avltree, special single left rotation]\n" );
                    k1 = special_left_rotation( k1 );
                    if ( NULL == k1 -> father ) t = k1;

                } else {
                    printf( "[delete_avltree right left rotation]\n" );
                    k1 = right_left_rotation( k1 );
                    if ( NULL == k1 -> father ) t = k1;
                }
        }
    }

    check_whole_tree_blanace( t );
    if( last_check != NULL ) {
        printf( "[delete_avltree, check_whole_tree_blanace] last_check.key = %d\n", last_check -> key );
        printf("[delete_avltree, check_whole_tree_blanace] get_node_height( last_check -> left ) = %d\n", get_node_height( last_check -> left ) );
        printf("[delete_avltree, check_whole_tree_blanace] get_node_height( last_check -> right ) = %d\n", get_node_height( last_check -> right ) );
        if( get_node_height( last_check -> left ) > get_node_height( last_check -> right ) ) {
            if ( NULL == last_check -> right && NULL == last_check -> left -> right ) {
                Node* tmp =  right_rotation( last_check );
                print_node_info( "[delete_avltree, check_whole_tree_blanace, right_rotation]", tmp );
            } else if ( NULL == last_check -> right
                && get_node_height( last_check -> left -> left ) == get_node_height( last_check -> left -> right ) )
            {
                Node* tmp = special_right_rotation( last_check );
                print_node_info( "[delete_avltree, check_whole_tree_blanace, special_right_rotation]", tmp );
            } else if ( NULL == last_check -> right
                &&  ( NULL == last_check -> left -> left || NULL == last_check -> left -> right ) )
            {
                Node* tmp =  special_right_rotation( last_check );
                print_node_info( "[delete_avltree, check_whole_tree_blanace, special_right_rotation]", tmp );
            }

            last_check = NULL;

        } else if (  get_node_height( last_check -> left ) < get_node_height( last_check -> right ) ) {

            if ( NULL == last_check -> left && NULL == last_check -> right -> left ) {
                Node* tmp =  left_rotation( last_check );
                print_node_info( "[delete_avltree, check_whole_tree_blanace, left_rotation]", tmp );
            } else if ( NULL == last_check -> left
                && get_node_height( last_check -> right -> left ) == get_node_height( last_check -> right -> right ) )
            {
                Node* tmp = special_left_rotation( last_check );
                print_node_info( "[delete_avltree, check_whole_tree_blanace, special_left_rotation]", tmp );
            } else if ( NULL == last_check -> left
                &&  ( NULL == last_check -> right -> left || NULL == last_check -> right -> right ) )
            {
                Node* tmp =  special_left_rotation( last_check );
                print_node_info( "[delete_avltree, check_whole_tree_blanace, special_left_rotation]", tmp );
            }

            last_check = NULL;

        }
    }


    return t;
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
                    printf( "[avltree_insert single left rotation]\n" );
                    k1 = right_rotation( k1 );
                    if ( NULL == k1 -> father ) t = k1; //change root node
                } else {
                    printf( "[avltree_insert left right rotation]\n" );
                    k1 = left_right_rotation( k1 );
                    if ( NULL == k1 -> father ) t = k1;
                }

        } else if ( get_node_height( k1 -> left  ) < get_node_height( k1 -> right ) ) {
                printf( "====================> get_node_height( k1 -> right -> left ) = %d\n", get_node_height( k1 -> right -> left ) );
                printf( "====================> get_node_height( k1 -> left ) = %d\n", get_node_height( k1 -> left ) );
                if ( get_node_height( k1 -> right -> left ) == get_node_height( k1 -> left ) ) {
                    printf( "[avltree_insert single right rotation]\n" );
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

// 0 NULL, 1 single, 2 root, 4, leaf, 3 TRUNk
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
    printf( "[left_rotation] k1 -> key = %d\n",  k1 -> key );
    printf( "[left_rotation] get_node_height( k1 -> right ) = %d, get_node_height( k1 -> left ) = %d\n", get_node_height( k1 -> right ), get_node_height( k1 -> left ) );
    printf( "[left_rotation] get_node_height( k1 -> right ) - get_node_height( k1 -> left ) = %d\n", get_node_height( k1 -> right ) - get_node_height( k1 -> left ) );
    if ( 2 == get_node_height( k1 -> right ) - get_node_height( k1 -> left ) ) {
        Node* k2 = k1 -> right;
        if ( NULL == k1 -> left &&  NULL == k2 -> left ) {
            k2 -> father = k1 -> father;
            k1 -> right = NULL;
            k2 -> left = k1;
            k1 -> father = k2;

        } else if ( 1 == get_node_height( k1 -> left ) && 0 == get_node_height( k2 -> left ) ) {
            printf( "<=======================>\n" );
            k2 -> father = k1 -> father;
            k1 -> right = NULL;
            k2 -> left = k1;
            k1 -> father = k2;
        } else {
            Node* k3 = k2 -> left;
            k2 -> father = k1 -> father;
            k2 -> left = k1;
            k1 -> father = k2;
            k1 -> right = k3;
            k3 -> father = k1;
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
        printf( "[left_right_rotation, left_rotation] k1 = ( %d )%p, k2 = %p\n", k1 -> key, k1, k1 -> right );
        Node* k2 = k1 -> right;
        printf( "[left_right_rotation, left_rotation] k2 = %p, k2 -> key = %d\n", k2, k2 -> key );
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
        printf( "[right_rotation,  single] k1 -> key = %d, k2 -> key = %d\n", k1 -> key, k2 -> key );
        if ( NULL == k1 -> right &&  NULL == k2 -> right ) {
            k2 -> father = k1 -> father;
            k1 -> left = NULL;
            k2 -> right = k1;
            k1 -> father = k2;

        } else if ( 1 == get_node_height( k1 -> right ) && 0 == get_node_height( k2 -> right ) ) {
            printf( "<=======================>\n" );
            k2 -> father = k1 -> father;
            k1 -> left = NULL;
            k2 -> right = k1;
            k1 -> father = k2;
        } else {
            Node* k3 = k2 -> right;
            k2 -> father = k1 -> father;
            k2 -> right = k1;
            k1 -> father = k2;
            k1 -> left = k3;
            k3 -> father = k1;
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

static Node *bstree_delete( AvlTree t, Node *n )
{
    int type = get_node_type( n );
    if ( 0 == type )
        return NULL;
    printf( "%d 's type %d\n", n->key, type );
    if ( 1 == type )
    {
        free( n );
        return NULL;
    }

    if ( 4 == type )
    {
        if ( n->father->left == n )
            n->father->left = NULL;
        else
            n->father->right = NULL;

        free( n );
    }
    else // if(2 == type)
    {
        if ( n->left != NULL && n->right == NULL )
        {
            Node *p = avltree_precursor( n );
            if ( 4 == get_node_type( p ) )
            {
                if ( p->father->left == p )
                    p->father->left = NULL;
                else
                    p->father->right = NULL;
            }
            else
            {
                if ( p->left != NULL )
                {
                    if ( p->father->left == p )
                        p->father->left = p->left;
                    else
                        p->father->right = p->left;

                    p->left->father = p->father;
                }
                else
                {
                    if ( p->father->left == p )
                        p->father->left = p->right;
                    else
                        p->father->right = p->right;

                    p->right->father = p->father;
                }
            }

            n->key = p->key;
            free( p );
        }
        else if ( n->right != NULL )
        {
            Node *s = avltree_successor( n );
            if ( 4 == get_node_type( s ) )
            {
                if ( s->father->left == s )
                    s->father->left = NULL;
                else
                    s->father->right = NULL;
            }
            else
            {
                if ( s->left != NULL )
                {
                    if ( s->father->left == s )
                        s->father->left = s->left;
                    else
                        s->father->right = s->left;

                    s->left->father = s->father;
                }
                else
                {
                    if ( s->father->left == s )
                        s->father->left = s->right;
                    else
                        s->father->right = s->right;

                    s->right->father = s->father;
                }
            }

            n->key = s->key;
            free( s );
        }
    }

    return t;
}


static Node* lost_balance_node( Node * t )
{
    Node* ret = NULL;
    Node* tmp = t;

    do {

        if ( NULL == tmp ) break;

        int diff = get_node_height( tmp -> left )  - get_node_height( tmp -> right );
        printf( "[lost_balance_node] tmp -> key = %d( %p ), diff = %d\n", tmp -> key, tmp, diff );
        printf( "get_node_height( tmp -> left ) = %d\n", get_node_height( tmp -> left ) );
        printf( "get_node_height( tmp -> right ) = %d\n", get_node_height( tmp -> right ) );
        if( 2 == abs( diff ) ) {
            ret = tmp;
            printf( "[lost_balance_node]  found lost blance Node address is %p, value is %d\n", ret , ret -> key );
            break;
        }

        tmp = tmp -> father;

    } while( 1 );

    return ret;
}

static Node* special_left_rotation( Node * k1 )
{
    Node * k2 = k1 -> right;
    Node * k3 = k2 -> left;

    int type = check_node_type( k1 );
    printf( "[special_left_rotation] k1 = %d, get_node_type( k1 ) = %d\n", k1 -> key ,get_node_type( k1 ) );

    k2 -> father = k1 -> father;
    k2 -> left = k1;
    k1 -> father = k2;
    k1 -> right = k3;
    k3 -> father = k1;

    if ( 3 == type ) {
        k2 -> father -> left  = k2;
    } else if ( 4 == type ) {
        k2 -> father -> right  = k2;
    }

    return k2;

}


static Node* special_right_rotation( Node * k1 )
{
    Node * k2 = k1 -> left;
    Node * k3 = k2 -> right;

    int type = check_node_type( k1 );

    k2 -> father = k1 -> father;
    k2 -> right = k1;
    k1 -> father = k2;
    k1 -> left = k3;
    k3 -> father = k1;

    if ( 3 == type ) {
        k2 -> father -> left  = k2;
    } else if ( 4 == type ) {
        k2 -> father -> right  = k2;
    }

    return k2;
}


static void print_node_info( const char* msg, Node * t )
{
    if ( NULL == t ) {
        printf( "[%s] the node is NULL\n", msg );
        return;
    }

    Node* father = t -> father;
    Node* left = t -> left;
    Node* right = t -> right;

    printf( "[%s]the Node information: key %d ", msg ,t -> key );
    if ( NULL != father  ) {
        printf( ", father %d ", father -> key );
    }

    if ( NULL != left ) {
        printf( ", left %d ", left -> key );
    }

    if ( NULL != right ) {
        printf( ", right %d ", right -> key );
    }

    printf( "\n" );

}


static void check_whole_tree_blanace( Node* t )
{
    printf( "<-----------check_whole_tree_blanace----------->\n" );
    printf( "t = %p, last_check = %p\n", t, last_check );
    if ( t != NULL ) {
        int diff = get_node_height( t -> left ) - get_node_height( t -> right );
        if ( abs( diff ) > 1 ) {
            printf( "[check_whole_tree_blanace, diff] diff = %d, t -> key = %d\n", diff, t -> key );
            last_check = t;
            return;

        } else {
            check_whole_tree_blanace( t -> left );
            check_whole_tree_blanace( t -> right );
        }
    }
}


