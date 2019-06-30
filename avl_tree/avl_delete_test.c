#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl_tree.h"

static Node* delete_tree_node( AvlTree t, int key );
static int randomIndex();
static void loop_random_test();
static void step_delete_test();

int array[ 10 ] = { 75, 37, 85, 28, 84, 33, 93, 17, 65, 57 };


int main(int argc, char const *argv[])
{
	//loop_random_test();
	step_delete_test();
	return 0;
}

static void step_delete_test()
{
    AvlTree t = NULL;
    int i;
    for ( i = 0; i < 10; i++ ) {
        t = insert_avltree( t, array[ i ] );
        printf( "[Main]\n" );
        print_avltree( t, t -> key , 0 );
        printf( "\n" );
    }

    printf("========================\n");	

    t = delete_tree_node( t, 28 );
    t = delete_tree_node( t, 17 );
    t = delete_tree_node( t, 65 );
    t = delete_tree_node( t, 85 );
    t = delete_tree_node( t, 84 );
    // t = delete_tree_node( t, 57 );
    // t = delete_tree_node( t, 28 );
    // t = delete_tree_node( t, 28 );
    // t = delete_tree_node( t, 93 );
    // t = delete_tree_node( t, 37 );
    // t = delete_tree_node( t, 65 );

    destroy_avltree( t );	
}



static void loop_random_test()
{
	
	srand( time( NULL ) );

	int i, counter = 0;
	do {

		printf("Test case [%d]\n", counter );

        AvlTree t = NULL;
        for ( i = 0; i < 10; i++ ) {
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


	} while ( counter < 100 );

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