#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl_tree.h"

static Node* delete_tree_node( AvlTree t, int key );
static int randomIndex();
static void loop_random_test( int array[], int size, int test_counter );
static void step_delete_test(int r);

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


int main(int argc, char const *argv[])
{
    int i, j;
    printf( "sizeof( array ) / sizeof( array[0] ) = %ld\n", sizeof( array ) / sizeof( array[0] ) );
    printf( " sizeof( array[0] ) / sizeof( int ) = %ld\n",  sizeof( array[ 0 ] ) / sizeof( int ) );

    for( i = 0; i < sizeof( array ) / sizeof( array[0] ); i++ ) {
        loop_random_test( array[ i ], sizeof( array[i] ) / sizeof( int ), 100 );
    }

    //loop_random_test( array[ 5 ], 10, 1000 );

	//step_delete_test( 5 );
	return 0;
}

static void step_delete_test( int r )
{
    AvlTree t = NULL;
    int i;
    for ( i = 0; i < 10; i++ ) {
        t = insert_avltree( t, array[ r ][ i ] );
        printf( "[Main]\n" );
        print_avltree( t, t -> key , 0 );
        printf( "\n" );
    }

    printf("========================\n");

    t = delete_tree_node( t, 35 );
    t = delete_tree_node( t, 71 );
    t = delete_tree_node( t, 89 );
    // t = delete_tree_node( t, 99 );
    // t = delete_tree_node( t, 17 );
    // t = delete_tree_node( t, 57 );
    // t = delete_tree_node( t, 73 );
    // t = delete_tree_node( t, 33 );
    // t = delete_tree_node( t, 37 );
    // t = delete_tree_node( t, 37 );
    // t = delete_tree_node( t, 65 );

    destroy_avltree( t );
}



static void loop_random_test( int array[], int size, int test_counter )
{

	srand( time( NULL ) );

	int i, counter = 0;
	do {

		printf("Test case [%d]\n", counter );

        AvlTree t = NULL;
        for ( i = 0; i < size; i++ ) {
            t = insert_avltree( t, array[ i ] );
            printf( "[Main]\n" );
            print_avltree( t, t -> key , 0 );
            printf( "\n" );
        }

        while ( t != NULL ) {
            int idx = randomIndex();
            int key = array[ idx ];
            printf( "idx = %d, key = %d\n", idx, key );
            t = delete_tree_node( t, key );
        }

        counter++;


	} while ( counter < test_counter );

	printf( "\n\n%s\n\n", "Well done!");

}


static int randomIndex()
{
	return rand() % 10;
}

static Node* delete_tree_node( AvlTree t, int key )
{

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
