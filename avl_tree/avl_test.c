#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl_tree.h"

static Node* delete_tree_node( AvlTree t  ,int key );

static int randomIndexGen();

int main(int argc, char const *argv[])
{
    int arr[ 10 ] = { 0 };

    srand( time( NULL ) );

    int array[ 10 ][ 10 ] = {
         { 49, 60, 35, 32, 68, 14, 69, 51, 33, 47 },
         { 43, 46, 51, 69, 92, 73, 65, 41, 81, 38 },
         { 93, 59, 86, 33, 17, 76, 75, 88, 98, 95 },
         { 37, 20, 97, 62, 42, 27, 29, 64, 68, 14 },
         { 63, 12, 66, 33, 94, 39, 50, 35, 72, 79 },
         { 28, 83, 65, 13, 90, 41, 79, 92, 36, 68 },
         { 12, 85, 83, 97, 64, 23, 32, 68, 76, 86 },
         { 33, 95, 71, 27, 34, 21, 15, 59, 90, 85 },
         { 42, 56, 89, 85, 49, 30, 26, 93, 84, 96 },
         { 42, 67, 93, 96, 83, 68, 29, 52, 44, 37 }
    };

    int i, j;

    for ( i = 1; i < 2; i++ ) {
        printf( "==========array[%d]==========\n", i );
        printf( "Input Numbers : " );
        for( j = 0; j < 10; j++ ) {
            printf( "%d ", array[ i ][ j ] );
        }
        printf( "\n\n" );

        AvlTree t = NULL;
        for ( j = 0; j < 10; j++ ) {
            t = insert_avltree( t, array[ i ][ j ] );
            printf( "[Main]\n" );
            print_avltree( t, t -> key , 0 );
            printf( "\n" );
        }

        while ( t != NULL ) {
            int idx = randomIndexGen();
            int key = array[ i ][ idx ];
            printf( "idx = %d, key = %d\n", idx, key );
            t = delete_tree_node( t, key );
        }

        //destroy_avltree( t );

    }

    return 0;
}

static Node* delete_tree_node( AvlTree t  ,int key ) {

    if( NULL == t ) return NULL;

    printf( "===============================> Before delete Node( %d )\n", key );
    print_avltree( t, t -> key, 0 );

    t = delete_avltree( t, key );
    printf( "===============================> After delete Node( %d ):\n", key );
    if ( NULL != t )
        print_avltree(t, t -> key, 0 );
    else
        printf( "the AvlTree is empty!\n" );

    return t;
}

static int randomIndexGen()
{
    return rand() % 10;
}


