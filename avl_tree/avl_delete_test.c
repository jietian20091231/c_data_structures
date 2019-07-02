#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl_tree.h"

static Node* delete_tree_node( AvlTree t, int key );
static int randomIndex();
static void loop_random_test( int array[], int size, int test_counter );
static void step_delete_test(int r);

int array[ 10 ][ 10 ] = {
 { 37, 57, 30, 17, 73, 77, 96, 18, 99, 27 },    //0
 { 59, 96, 50, 13, 15, 93, 36, 91, 67, 75 },    //1
 { 44, 90, 39, 82, 18, 94, 29, 74, 31, 38 },    //2
 { 94, 90, 63, 34, 49, 72, 85, 56, 51, 44 },    //3
 { 52, 91, 48, 19, 84, 36, 69, 37, 55, 44 },    //4
 { 71, 45, 35, 67, 79, 95, 62, 61, 69, 89 },    //5
 { 25, 36, 53, 11, 75, 77, 87, 31, 28, 83 },    //6
 { 36, 19, 31, 45, 55, 20, 66, 44, 65, 10 },    //7
 { 67, 63, 87, 34, 42, 82, 86, 55, 13, 84 },    //8
 { 45, 29, 20, 50, 30, 47, 79, 69, 68, 59 }     //9
};


int main(int argc, char const *argv[])
{
    int i, j;
    printf( "sizeof( array ) / sizeof( array[0] ) = %ld\n", sizeof( array ) / sizeof( array[0] ) );
    printf( " sizeof( array[0] ) / sizeof( int ) = %ld\n",  sizeof( array[ 0 ] ) / sizeof( int ) );

    // for( i = 0; i < sizeof( array ) / sizeof( array[0] ); i++ ) {
    //     loop_random_test( array[ i ], sizeof( array[i] ) / sizeof( int ), 100 );
    // }

    //loop_random_test( array[ 5 ], 10, 1000 );

	step_delete_test( 5 );
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
