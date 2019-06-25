#include <stdio.h>
#include "avl_tree.h"

int main(int argc, char const *argv[])
{
    //int arr[ 10 ] = { 25, 88, 70, 18, 21, 45, 42, 97, 22, 11 };
    //int arr[ 10  ] = { 62, 33, 86, 69, 84, 53, 20, 80, 48, 68 };
    //int arr[ 10 ] = { 16, 29, 40, 36, 33, 68, 42, 49, 50, 52 };

    int arr[ 10 ] = { 33, 28, 94, 16, 39, 81, 44, 34, 66, 74 };

    int i;

    AvlTree t = NULL;

    for ( i = 0; i < 10; i++ ) {
        t = insert_avltree( t, arr[ i ] );
        printf( "[Main]\n" );
        print_avltree( t, t -> key , 0 );
        printf( "\n" );
    }

    destroy_avltree( t );

    return 0;
}


