#include <stdio.h>
#include "avl_tree.h"

int main(int argc, char const *argv[])
{
    int arr[ 10 ] = { 25, 88, 70, 18, 21, 45, 42, 97, 22, 11 };

    AvlTree t = NULL;

    t = insert_avltree( t, arr[ 0 ] );
    print_avltree( t, t -> key , 0 );

    t = insert_avltree( t, arr[ 1 ] );
    print_avltree( t, t->key, 0 );

    t = insert_avltree( t, arr[ 2 ] );
    print_avltree( t, t->key, 0 );

    destroy_avltree( t );

    return 0;
}


