#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl_tree.h"

#define ROW  1
#define COL  10

int array[ ROW ][ COL ];


static void initArray( void )
{
    int i,j;
    for ( i = 0; i < ROW; i++ ) {
        for ( j = 0; j < COL; j++ )
            array[ i ][ j ] = 0;
    }
}

static void randomGen( int r[] )
{
    r[ 0 ] = rand() % 90 + 10;

    int i, j ;
    for ( i = 1; i < COL; i++ ) {
        int n = rand() % 90 + 10;
        int flag = 1;
        do {
            for ( j = 0; j < i; j++ ) {
                if ( n == r[ j ] ) {
                    n = rand() % 90 + 10;
                } else {
                    flag = 0;
                }
            }

        } while ( flag );

        r[ i ] = n;
    }
}

int main(int argc, char const *argv[])
{
    int i, j;
    srand( time( NULL  ) );

    for ( i = 0; i < ROW; i++ ) {
        randomGen( array [ i ] );
    }

    // for ( i = 0; i < ROW; i++ ) {
    //     printf( "[ %d ] : ", i );
    //     for ( j = 0; j < COL; j++ ) {
    //         printf( "%d ", array[ i ][ j ] );
    //     }
    //     printf( "\n" );
    // }


    for( i = 0 ; i < ROW; i++ ) {
        printf( "====================Avl tree [%d]====================\n", i );
        printf( "array[%d] : ", i );
        for ( j = 0; j < COL; j++ ) {
            printf( "%d ", array[ i ][ j ] );
        }
        printf( "\n" );
        AvlTree avl = NULL;
        for( j = 0; j < COL; j++ ) {
            printf( "array[ %d ][ %d ]  = %d\n", i, j,  array[ i ][ j ] );
            avl = insert_avltree( avl, array[ i ][ j ] );
        }

        printf( "avl address = %p, ", avl );
        printf("avl tree deepth : %d\n", get_node_height( avl ) );

        printf("preorder traversal:\n");
        preorder_avltree( avl );

        printf("\ninorder traversal:\n");
        inorder_avltree( avl );

        printf("\npostorder traversal:\n");
        postorder_avltree( avl );

        Node *n = avltree_maximum( avl );
        printf("\nFind avl maximum's %d.", n->key);

        n = avltree_minimum( avl );
        printf("\nFind avl minimum's %d.", n->key);

        int searchKey = 7;
        n = avltree_search( avl, searchKey );
        if ( NULL == n )
        {
            printf( "\nCan't found %d in avl tree.", searchKey );
        }
        else
        {
            printf( "\nthe key[%d] is found in avltree.", n->key );
            Node *p = avltree_precursor( n );
            if ( NULL != p )
            {
                printf( "Node[%d] has a precursor Node[%d].\n", n->key, p->key );
            }
        }

        printf( "\nshow avl tree :\n" );

        print_avltree( avl, avl -> key, 0 );

        destroy_avltree( avl );

        printf("\n");
        printf("=====================================================\n");
    }


    return 0;
}
